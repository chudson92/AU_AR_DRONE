/*
 * Controler.cpp
 *
 *  Created on: Jun 27, 2013
 *      Author: chris
 */
#include <iostream>
#include "Controler.h"
#include "Controls.h"
#include "XbeeIO.h"
#include <unistd.h>
extern "C" {
#include "scanner.h"

}

using namespace std;

void controller() {
	//cout << " IN THE CONTROLLER " << endl;
	bool autonomous = true;
	int topSensor[5];
	int frontSensor[5];
	int leftSensor[5];
	int rightSensor[5];
	int backSensor[5];

	takeoff();
	sleep(10);
	land();

	//while (autonomous == true) {
		//cout << "IN WHILE LOOP" << endl;
		//char* str;
		//receive(str, 4);
		//cout << " AFTER RECIEVE " << endl;
		//int scanTimes = 5;

		//std::cout << "After SCANTIMES" << std::endl;

		/*scanSensors(scanTimes, topSensor, frontSensor, leftSensor, rightSensor, backSensor);
		//cout << topSensor[5] << endl;

		if (topSensor[2] <= 3528) { //if closer then 2 ft above
			stop();
			down();
			stop();

		}

		//TODO: Implement a protocal for going around
		if (frontSensor[2] <= 5292) { //if closer then 2 ft front
			stop();
			back();
			stop();
			sleep(3);
			land();

		}
		if (leftSensor[2] <= 100) { //if closer then 2 ft left
			stop();
			right();
			stop();

		}
		if (rightSensor[2] <= 100) { //if closer then 2 ft right
			stop();
			left();
			stop();

		}
		if (backSensor[2] <= 100) { //if closer then 2 ft back
			stop();
			forward();
			stop();

		}
		sleep(1);

//		forward();

	//}*/
}
