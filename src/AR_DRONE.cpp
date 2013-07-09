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
		bool dia = diagnostics(); //launch diagnostics

		//if diagnostics return true launch
		bool i = true;
		if (i == dia) {
			char* launch = "launch?";
			char* launchResponse = "launch";
			sendMsg(launch);

			char message[7];
			receive(message, 6);

			if (strcmp(launchResponse, message) == 0) {
				controller();

			} else {
				cout << "STRING COMPARISON FAILED" << endl;
				return false;
			}

		} else {
			cout << "FAILED TO RECIEVE MESSAGE CALLING EXIT()" << endl;
			exit(EXIT_FAILURE);
		}

	}
