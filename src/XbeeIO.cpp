// Standard includes
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cmath>
#include <string.h>
#include <inttypes.h>
#include <fstream>
// Serial includes
#include <stdio.h> /* Standard input/output definitions */
#include <string.h> /* String function definitions */
#include <unistd.h> /* UNIX standard function definitions */
#include <fcntl.h> /* File control definitions */
#include <errno.h> /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#ifdef __linux
#include <sys/ioctl.h>
#include <termios.h>
#endif

using std::string;
using namespace std;

struct timeval tv; ///< System time

int baud = 57600; ///< The serial baud rate
// Settings
int sysid = -1; ///< The unique system id of this MAV, 0-127. Has to be consistent across the system
int compid = 110;
int serial_compid = 0;
std::string port = "/dev/ttyUSB0"; ///< The serial port name, e.g. /dev/ttyUSB0
bool silent = false; ///< Wether console output should be enabled
bool verbose = false; ///< Enable verbose output
bool debug = false; ///< Enable debug functions and output
bool pc2serial = true; ///< Enable PC to serial push mode (send more stuff from pc over serial)
int fd; ///< file descriptor of port

int updateIndex = 0; ///<To keep number of AU_UAV MAVLink messages
int WPSendSeqNum = 0; ///<Int to keep up with number of wp's sent to UAV
int myMessages[256]; ///< Array to keep up with which messages are sent

bool readyToStart = false;

int open_port(std::string& port) {
	int fd; /* File descriptor for the port */

// Open serial port
// O_RDWR - Read and write
// O_NOCTTY - Ignore special chars like CTRL-C
	fd = open(port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd == -1) {
		/* Could not open the port. */
		return (-1);
	} else {
		fcntl(fd, F_SETFL, 0);
	}

	return (fd);
}

bool setup_port(int fd, int baud, int data_bits, int stop_bits, bool parity,
		bool hardware_control) {
//struct termios options;

	struct termios config;
	if (!isatty(fd)) {
		fprintf(stderr, "\nERROR: file descriptor %s is NOT a serial port\n",
				port.c_str());
		return false;
	}
/*	if (tcgetattr(fd, &config) < 0) {
		fprintf(stderr, "\nERROR: could not read configuration of port %s\n",
				port.c_str());
		return false;
	}*/


	config.c_cc[VMIN]  = 0;
	config.c_cc[VTIME] = 10;

//
// Input flags - Turn off input processing
// convert break to null byte, no CR to NL translation,
// no NL to CR translation, don't mark parity errors or breaks
// no input parity check, don't strip high bit off,
// no XON/XOFF software flow control
//
/*	config.c_iflag &= ~(IGNBRK | BRKINT | ICRNL | INLCR | PARMRK | INPCK
			| ISTRIP | IXON);*/
//
// Output flags - Turn off output processing
// no CR to NL translation, no NL to CR-NL translation,
// no NL to CR translation, no column 0 CR suppression,
// no Ctrl-D suppression, no fill characters, no case mapping,
// no local output processing
//
// config.c_oflag &= ~(OCRNL | ONLCR | ONLRET |
// ONOCR | ONOEOT| OFILL | OLCUC | OPOST);
	config.c_oflag = 0;
//
// No line processing:
// echo off, echo newline off, canonical mode off,
// extended input processing off, signal chars off
//
	config.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
//
// Turn off character processing
// clear current char size mask, no parity checking,
// no output processing, force 8 bit input
//
	config.c_cflag &= ~(CSIZE | PARENB);
	config.c_cflag |= CS8;
//
// One input byte is enough to return from read()
// Inter-character timer off
//
	config.c_cc[VMIN] = 0;
	config.c_cc[VTIME] = 20; // was 0

// Get the current options for the port
//tcgetattr(fd, &options);

	switch (baud) {
	case 1200:
		if (cfsetispeed(&config, B1200) < 0
				|| cfsetospeed(&config, B1200) < 0) {
			fprintf(stderr,
					"\nERROR: Could not set desired baud rate of %d Baud\n",
					baud);
			return false;
		}
		break;
	case 1800:
		cfsetispeed(&config, B1800);
		cfsetospeed(&config, B1800);
		break;
	case 9600:
		cfsetispeed(&config, B9600);
		cfsetospeed(&config, B9600);
		break;
	case 19200:
		cfsetispeed(&config, B19200);
		cfsetospeed(&config, B19200);
		break;
	case 38400:
		if (cfsetispeed(&config, B38400) < 0
				|| cfsetospeed(&config, B38400) < 0) {
			fprintf(stderr,
					"\nERROR: Could not set desired baud rate of %d Baud\n",
					baud);
			return false;
		}
		break;
	case 57600:
		if (cfsetispeed(&config, B57600) < 0
				|| cfsetospeed(&config, B57600) < 0) {
			fprintf(stderr,
					"\nERROR: Could not set desired baud rate of %d Baud\n",
					baud);
			return false;
		}
		break;
	case 115200:
		if (cfsetispeed(&config, B115200) < 0
				|| cfsetospeed(&config, B115200) < 0) {
			fprintf(stderr,
					"\nERROR: Could not set desired baud rate of %d Baud\n",
					baud);
			return false;
		}
		break;
	default:
		fprintf(stderr,
				"ERROR: Desired baud rate %d could not be set, falling back to 115200 8N1 default rate.\n",
				baud);
		cfsetispeed(&config, B115200);
		cfsetospeed(&config, B115200);

		break;
	}

//
// Finally, apply the configuration
//
	if (tcsetattr(fd, TCSAFLUSH, &config) < 0) {
		fprintf(stderr, "\nERROR: could not set configuration of port %s\n",
				port.c_str());
		return false;
	}
	return true;
}

bool close_port(int fd) {
	if (verbose) {
		printf("\n");
		printf("\n");
		printf("Printing myMessages array: \n");
		int i;
		for (i = 0; i < 256; i++)
			if (myMessages[i] > 0)
				printf("#%d: %d\n", i, myMessages[i]);
	}
	close(fd);
	return true;
}

void receive(char* str, int messageLength) {

	if (verbose) {
		int j;
		for (j = 0; j < 256; j++)
			myMessages[j] = 0;
	}

// SETUP SERIAL PORT

// Exit if opening port failed
// Open the serial port.
	if (!silent)
		printf("Trying to connect to %s.. ", port.c_str());
	fd = open_port(port);
	if (fd == -1) {
		if (!silent)
			fprintf(stderr, "failure, could not open port.\n");
		exit(EXIT_FAILURE);
	} else {
		if (!silent)
			printf("success.\n");
	}
	if (!silent)
		printf("Trying to configure %s.. ", port.c_str());
	bool setup = setup_port(fd, baud, 8, 1, false, false);
	if (!setup) {
		if (!silent)
			fprintf(stderr, "failure, could not configure port.\n");
		exit(EXIT_FAILURE);
	} else {
		if (!silent)
			printf("success.\n");
	}
	int* fd_ptr = &fd;

	int noErrors = 0;
	if (fd == -1 || fd == 0) {
		if (!silent)
			fprintf(stderr,
					"Connection attempt to port %s with %d baud, 8N1 failed, exiting.\n",
					port.c_str(), baud);
		exit(EXIT_FAILURE);
	} else {
		if (!silent)
			fprintf(stderr,
					"\nConnected to %s with %d baud, 8 data bits, no parity, 1 stop bit (8N1)\n",
					port.c_str(), baud);

	}

// FIXME ADD MORE CONNECTION ATTEMPTS

	if (fd == -1 || fd == 0) {
		exit(noErrors);
	}

// Ready to roll

// Send message over serial port

	int i = 0;
	char* ptr;

	ptr = str;
	str[messageLength] = '\0';

	std::cout << "Run Initialize on Ground Station please" << std::endl;
	while (1) {

		if (read(fd, ptr, 1) > 0) {
			ptr++;
			i++;
		}
		if (i == messageLength) {
			break;
		}

	}

	//cout << "Printing from XbeeIO's receive()..." << endl;
	//cout << str << endl;
	flush(cout);
	close_port(fd);

}

void sendMsg(char* message) {
	char* buf = message;
	 int messageLength = sizeof(buf);
	 cout << buf << endl;
	 int test = write(fd, buf, messageLength);
	 tcflush(fd, TCOFLUSH);
	 //if (messageLength != test) fprintf(stderr, "ERROR: Wrote %d bytes in send(char* message) but should have written %d\n", test, messageLength);

}

void receiveQuick(char* str, int messageLength) {

	if (verbose) {
		int j;
		for (j = 0; j < 256; j++)
			myMessages[j] = 0;
	}

// SETUP SERIAL PORT

// Exit if opening port failed
// Open the serial port.
	if (!silent)
		printf("Trying to connect to %s.. ", port.c_str());
	fd = open_port(port);
	if (fd == -1) {
		if (!silent)
			fprintf(stderr, "failure, could not open port.\n");
		exit(EXIT_FAILURE);
	} else {
		if (!silent)
			printf("success.\n");
	}
	if (!silent)
		printf("Trying to configure %s.. ", port.c_str());
	bool setup = setup_port(fd, baud, 8, 1, false, false);
	if (!setup) {
		if (!silent)
			fprintf(stderr, "failure, could not configure port.\n");
		exit(EXIT_FAILURE);
	} else {
		if (!silent)
			printf("success.\n");
	}
	int* fd_ptr = &fd;

	int noErrors = 0;
	if (fd == -1 || fd == 0) {
		if (!silent)
			fprintf(stderr,
					"Connection attempt to port %s with %d baud, 8N1 failed, exiting.\n",
					port.c_str(), baud);
		exit(EXIT_FAILURE);
	} else {
		if (!silent)
			fprintf(stderr,
					"\nConnected to %s with %d baud, 8 data bits, no parity, 1 stop bit (8N1)\n",
					port.c_str(), baud);

	}

// FIXME ADD MORE CONNECTION ATTEMPTS

	if (fd == -1 || fd == 0) {
		exit(noErrors);
	}

// Ready to roll

// Send message over serial port

	int i = 0;
	char* ptr;

	ptr = str;
	str[messageLength] = '\0';

	//std::cout << "Run Initialize on Ground Station please" << std::endl;
	struct termios  config;
	config.c_cc[VMIN]  = 0;
	config.c_cc[VTIME] = 10;
	while (1) {

		int timeout = 250;
		if (read(fd, ptr, 1) > 0) {
			cout << "IN READQUICK: " << ptr << endl;
			ptr++;
			i++;
		}
		if (i == messageLength) {
			break;
		}

	}

	//cout << "Printing from XbeeIO's receive()..." << endl;
	//cout << str << endl;
	flush(cout);
	close_port(fd);
	return;

}
