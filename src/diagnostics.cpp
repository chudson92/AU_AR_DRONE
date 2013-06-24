#include <iostream>
#include "XbeeIO.h"
#include <string.h>

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
	char* xinit = "init";

	std::cout << "Initializing Xbee..." << std::endl;
	sleep(2);
	std::cout << "Run Initialize on Ground Station please" << std::endl;


	char* message = receive();

	if (strcmp(xinit,message) == 0)
		return true;
	else
		return false;
}

bool diagnostics() {

	bool sonarCheck = sonarInit();
	bool xbeeCheck = xbeeInit();

	if (sonarCheck) {
		cout << "Sonar............. Good" << endl;
		if (xbeeCheck) {
			cout << "Xbee............. Good" << endl;
		}

	} else
		return false;

	//Check Node.js running -> if not launch
	//get navdata
	//check battery -> return battery %

}

