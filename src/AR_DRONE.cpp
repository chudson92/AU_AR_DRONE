#include <stdio.h>
#include <stdlib.h>

#include <signal.h>
#include <string>
#include <string.h>
#include <sys/wait.h>
#include <iostream>
#include <sstream>
#include "xbee.h"
#include <unistd.h>								//this is what you need for fork, pipe, exec
#include "diagnostics.h"
#include "XbeeIO.h"
#include "nodelink.h"
#include <string>
#include <algorithm>
#include "Controler.h"
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <fstream>
#include <fcntl.h>
using namespace std;



void nodekill();



void nodekill(){
	system(" ps -ef | grep -w 'node repl.js' | cut -c10-15 | tail -2 | head -1 > PID.txt");
	ifstream pids;
	pids.open("PID.txt");
	int temp;
	pids>>temp;
	pids.close();
	kill(temp, SIGKILL);

}

	int main() {
		std::string port = "/dev/ttyUSB0";
		int fd = open_port(port);
		int baud = 57600;
		bool setup = setup_port(fd, baud, 8, 1, false, false);

		bool dia = diagnostics(fd); //launch diagnostics

		//if diagnostics return true launch


		SerialData myPacket2;
		init_serialData(myPacket2, '#', '!');
		myPacket2.fd = fd;

		if (dia) {
		//	printf("%d", myPacket2.fd);
			char* launch = "launch?";
			char* launchResponse = "launch";

			char message[7];
			while(!myPacket2.received){

			read_char(myPacket2);
			}

			cout << myPacket2.data << endl;
			if (strcmp(launchResponse, myPacket2.data) == 0) {
				controller(fd);

			} else {
				cout << "STRING COMPARISON FAILED" << endl;
				return false;
			}

		} else {
			cout << "FAILED TO RECIEVE MESSAGE CALLING EXIT()" << endl;
			exit(EXIT_FAILURE);
		}

	}
