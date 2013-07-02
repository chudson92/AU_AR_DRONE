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
	if (dist >= 8673) {
		std::cout << "Sonar Initialized" << std::endl;
		std::cout << dist / 147 << " inch clearance " << std::endl;
		return true;
	} else {
		std::cout << " Low clearance ... Takeoff blocked " << std::endl;
		return false;
	}
}

bool xbeeInit() {
	const char* xinit = "init";

	std::cout << "Initializing Xbee..." << std::endl;

	std::cout << "Run Initialize on Ground Station please" << std::endl;

	char message[5];
	receive(message, 4);
//	cout << "message recieved:" << message << endl;
	//cout << "strcmp returns... " << strcmp(xinit, message) << endl;
	if (strcmp(xinit, message) == 0)
		return true;
	else
		return false;
}

bool nodeInit() {
	//Check Node.js running -> if not launch
	//const char* battery = "drone> 100\ndrone>";
	const char* battery = "true";
	char* msgSend = "land()\n";
	char messageBack[4];
	cmd(msgSend,messageBack);

	cout << "message recieved in diagnostics: \n" << messageBack << endl;
	string str(messageBack);

	//cout << "conversted to str: " << str << endl;
	//str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
	// cout << "/n removed to str: " << str << endl;


	if (strcmp(messageBack, battery) == 0) {
		/*str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
		str.erase(std::remove(str.begin(), str.end(), 'd'), str.end());
		str.erase(std::remove(str.begin(), str.end(), 'r'), str.end());
		str.erase(std::remove(str.begin(), str.end(), 'o'), str.end());
		str.erase(std::remove(str.begin(), str.end(), 'n'), str.end());
		str.erase(std::remove(str.begin(), str.end(), 'e'), str.end());
		str.erase(std::remove(str.begin(), str.end(), '>'), str.end());*/

	//	cout << "battery life: " << str << endl;

		return true;
	} else {
		return false;
	}

}

bool diagnostics() {

	bool sonarCheck = sonarInit();
	if (sonarCheck) {
		cout << "Sonar............. Good" << endl;

	} else {
		cout << "Sonar initialization FAILED" << endl;
		exit(EXIT_FAILURE);
	}

	bool xbeeCheck = xbeeInit();
	if (xbeeCheck) {
		cout << "Xbee............. Good" << endl;

	} else {
		cout << "Xbee initialization FAILED" << endl;
		exit(EXIT_FAILURE);
	}

	bool nodeCheck = nodeInit();

	if (nodeCheck) {
		cout << "Node.js............. Good" << endl;

	} else{
		cout << "Node.js initialization FAILED" << endl;
		exit(EXIT_FAILURE);
	}

//get navdata
//check battery -> return battery %
	cout << "Diagnostics complete clear to launch()" << endl;
return true;
	//exit(EXIT_FAILURE);
}

