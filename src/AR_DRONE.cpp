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
/*

void takeoff() {
	const char* takeoff = " true\ndrone> ";
	char* goup = "takeoff()\n";
	char messageBack[18];
	writeMsg(goup);
	//readMsg(messageBack);
	//string str(messageBack);
	//cout << "MESSAGE RETURNED FROM READ : " << str << endl;

	//cout << "conversted to str: " << str << endl;
	//str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
	// cout << "/n removed to str: " << str << endl;


//	if (strcmp(messageBack, takeoff) == 0) {
		str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
		str.erase(std::remove(str.begin(), str.end(), 'd'), str.end());
		str.erase(std::remove(str.begin(), str.end(), 'r'), str.end());
		str.erase(std::remove(str.begin(), str.end(), 'o'), str.end());
		str.erase(std::remove(str.begin(), str.end(), 'n'), str.end());
		str.erase(std::remove(str.begin(), str.end(), 'e'), str.end());
		str.erase(std::remove(str.begin(), str.end(), '>'), str.end());
		cout<< "TAKEOFF WORKS" << endl;


//	}
//	else{
//		cout << "TAKEOFF STRING CMP FAILED" << endl;

//	}
}

	void land() {
		const char* land = "drone> true\ndrone";
		char* godown = "land()\n";
		char msgBack[18];
		writeMsg(godown);
		//readMsg(msgBack);
		//string str(msgBack);

		//cout << "conversted to str: " << str << endl;
		//str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
		// cout << "/n removed to str: " << str << endl;

		//if (strcmp(msgBack, land) == 0) {
			str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
			str.erase(std::remove(str.begin(), str.end(), 'd'), str.end());
			str.erase(std::remove(str.begin(), str.end(), 'r'), str.end());
			str.erase(std::remove(str.begin(), str.end(), 'o'), str.end());
			str.erase(std::remove(str.begin(), str.end(), 'n'), str.end());
			str.erase(std::remove(str.begin(), str.end(), 'e'), str.end());
			str.erase(std::remove(str.begin(), str.end(), '>'), str.end());

		//} else {

		//}
	}*/

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
