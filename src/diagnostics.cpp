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
	sleep(2);
	int dist = ping();

	//1.5m clearance (59 inches) drone flies at 1m
	if (dist >= 8673) {
		std::cout << "Sonar Initialized" << std::endl;
		std::cout << dist / 147 << " inch clearance " << std::endl;
		return true;
	} else {
		std::cout << " low clearance ... takeoff blocked " << std::endl;
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
	const char* battery = "drone> 100\ndrone>";

	char messageBack[17];
	cmd(messageBack);

	cout << "message recieved in diagnostics: \n" << messageBack << endl;
	 string str(messageBack);

	 //cout << "conversted to str: " << str << endl;
	 //str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
	// cout << "/n removed to str: " << str << endl;

	if (strcmp(messageBack, battery) == 0) {
		return true;
	} else {
		return false;
	}


}

bool diagnostics() {

	bool sonarCheck = sonarInit();
	bool xbeeCheck = xbeeInit();
	bool nodeCheck = nodeInit();

	if (sonarCheck) {
		cout << "Sonar............. Good" << endl;

	}
	if (xbeeCheck) {
		cout << "Xbee............. Good" << endl;

	}
	if (nodeCheck) {
		cout << "Node.js............. Good" << endl;

	} else
		return false;

//get navdata
//check battery -> return battery %

}

