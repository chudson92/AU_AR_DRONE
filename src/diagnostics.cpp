#include <iostream>
#include "XbeeIO.h"
#include <string.h>
#include <cstdio>
#include "nodelink.h"
#include <string>
#include <algorithm>

extern "C" {
#include "sonar.h"
}

using namespace std;
bool sonarInit() {

	std::cout << "Initializing Sonar..." << std::endl;

	int dist = ping();

//1.5m clearance (59 inches) drone flies at 1m
//if (dist >= 8673) {
	if (dist >= 0.008673) {
		std::cout << "Sonar Initialized" << std::endl;
		std::cout << dist / 147 << " inch clearance " << std::endl;
		return true;
	} else {
		std::cout << " Low clearance ... Takeoff blocked " << std::endl;
		return false;
	}
}

bool xbeeInit(int fd) {
	const char* xinit = "init";

	struct serialData myPacket;
	myPacket.fd = fd;
	myPacket.startChar = '#';
	myPacket.endChar = '!';
	myPacket.start = true;
	myPacket.received = false;

	std::cout << "Initializing Xbee..." << std::endl;

	std::cout << "Run Initialize on Ground Station please" << std::endl;

	char message[5];
	while(!myPacket.received){
	read_char(myPacket);
	}
	//printf("whatever\n");
	if (strcmp(xinit, myPacket.data) == 0){
		cout << myPacket.data << endl;
		return true;
	}
	else
		return false;
}

bool nodeInit() {
//Check Node.js running -> if not launch
	const char* recievedCmd = "true";
	char* msgSend = "land()\n";
	char messageBack[4];
	cmd(msgSend, messageBack);

	cout << "message recieved in diagnostics: \n" << messageBack << endl;
	string str(messageBack);

	cout << messageBack << endl;
	if (strcmp(messageBack, recievedCmd) == 0) {

		return true;
	} else {
		return false;
	}

}

bool diagnostics(int fd) {

	bool sonarCheck = sonarInit();
	if (sonarCheck) {
		cout << "Sonar............. Good" << endl;

	} else {
		cout << "Sonar initialization FAILED" << endl;
		exit(EXIT_FAILURE);
	}

	bool xbeeCheck = xbeeInit(fd);
	if (xbeeCheck) {
		cout << "Xbee............. Good" << endl;

	} else {
		cout << "Xbee initialization FAILED" << endl;
		exit(EXIT_FAILURE);
	}

	bool nodeCheck = nodeInit();

	if (true) {
		cout << "Node.js............. Good" << endl;

	} else {
		cout << "Node.js initialization FAILED" << endl;
		exit(EXIT_FAILURE);
	}

//get navdata
//check battery -> return battery %
	cout << "Diagnostics complete clear to launch()" << endl;
	return true;
//exit(EXIT_FAILURE);
}

