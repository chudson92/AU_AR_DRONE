
#include <fstream>
#include <fcntl.h>
// Standard includes
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cmath>
#include "XbeeIO.h"

#include <inttypes.h>
// Serial includes
#include <stdio.h> /* Standard input/output definitions */
#include <errno.h> /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#ifdef __linux
#include <sys/ioctl.h>
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
	if (tcgetattr(fd, &config) < 0) {
		fprintf(stderr, "\nERROR: could not read configuration of port %s\n",
				port.c_str());
		return false;
	}

	config.c_iflag &= ~(IGNBRK | BRKINT | ICRNL | INLCR | PARMRK | INPCK | ISTRIP | IXON);
	config.c_oflag =0;
	config.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
	config.c_cflag &= ~(CSIZE | PARENB);
	config.c_cflag |= CS8;
	config.c_cc[VMIN] = 0;
	config.c_cc[VTIME] = 10;





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
	}
	close(fd);
	return true;
}
void init_serialData(SerialData &d, char start, char end) {
    d.fd = -1;
    d.start = true;
    d.received = false;
    d.i = 0;
    d.startChar = start;
    d.endChar = end;
}

void read_quick(SerialData &myPacket) {
    if (myPacket.fd == -1) {
        return;
    }

    char buff;
    while (!myPacket.received) {

    	if (read(myPacket.fd, &buff, sizeof(char)) > 0) {

            if (myPacket.start) {
                if (buff == myPacket.startChar) {
                    myPacket.start = false;
                } else {
                    return;
                }
            } else {
                if (buff == myPacket.endChar) {

                    myPacket.received = true;
                    myPacket.i = 0;
                } else {
                    myPacket.data[myPacket.i] = buff;
                    myPacket.i++;
                }
            }
        }else{

        	return;
        }

    }
}

void read_char(SerialData &myPacket) {
//	printf("%d", myPacket.fd);
//	cout << " YO IM IN READ" << endl;
	if (myPacket.fd == -1) {
		return;
	}

	char buff;
	if (read(myPacket.fd, &buff, sizeof(char)) > 0) {
		printf("%c\n", buff);
		if (myPacket.start) {
			if (buff == myPacket.startChar) {
				myPacket.start = false;
			}
		} else {
			if (buff == myPacket.endChar) {
				myPacket.received = true;
				myPacket.data[myPacket.i] = '\0';
				myPacket.i = 0;
				tcflush(myPacket.fd, TCIFLUSH);
			} else {
				myPacket.data[myPacket.i] = buff;
				myPacket.i++;
			}
		}
	}
}

void sendMsg(char* message) {
	char* buf = message;
	int messageLength = sizeof(buf);
	cout << buf << endl;
	int test = write(fd, buf, messageLength);
	tcflush(fd, TCOFLUSH);
//if (messageLength != test) fprintf(stderr, "ERROR: Wrote %d bytes in send(char* message) but should have written %d\n", test, messageLength);

}

