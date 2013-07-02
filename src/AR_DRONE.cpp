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

void launchit();

void nodekill();

void launchit() {
	cout << "IN LAUNCHIT" << endl;

	cout << "PASSED CONTROLLER IN LAUNCHIT " << endl;
/*	sleep(10);
	takeoff();
	sleep(10);
	land();
	sleep(5);*/
	nodekill();
	sleep(2);

}

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

/*		int scans[5];
			scanner()
			scans[0] = 1;
			scans[1] = 2;
			scans[2] = 3;
			scans[3] = 4;
			scans[4] = 5;
			int j;
			for(j =0 ; j<5; j++)
			std::cout << "ONE SCAN IN CONTROLLER: " << scans[j] << std::endl;*/



		bool dia = diagnostics(); //launch diagnostics

		//if diagnostics return true launch
		bool i = true;
		if (i == dia) {
			char* launch = "launch?";
			char* launchResponse = "launch";
			sendMsg(launch);

			char message[7];
			receive(message, 6);

			cout << "message recieved:" << message << endl;
			//cout << "strcmp returns... " << strcmp(xinit, message) << endl;
			if (strcmp(launchResponse, message) == 0) {
				cout << "when you typed launch i recieved: " << message << endl;
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
