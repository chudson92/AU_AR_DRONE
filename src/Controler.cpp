/*
 * Controler.cpp
 *
 *  Created on: Jun 27, 2013
 *      Author: chris
 */

#include "Controler.h"
#include "Controls.h"
#include "XbeeIO.h"
#include <unistd.h>
extern "C" {
#include "scanner.h"
}

void controller() {

	bool autonomous;
	int topSensor[11];
	int frontSensor[11];
	int leftSensor[11];
	int rightSensor[11];
	int backSensor[11];
	while (autonomous == true) {

		char* str;
		receive(str, 4);
		int scanTimes = 11;



		scanSensors(scanTimes, topSensor, frontSensor, leftSensor, rightSensor, backSensor);

		if (topSensor[5] <= 3528) { //if closer then 2 ft above
			stop();
			down();
			sleep(1);
			stop();

		}

		//TODO: Implement a protocal for going around
		if (frontSensor[5] <= 3528) { //if closer then 2 ft front
			stop();
			back();
			sleep(1);
			stop();

		}
		if (leftSensor[5] <= 3528) { //if closer then 2 ft left
			stop();
			right();
			sleep(1);
			stop();

		}
		if (rightSensor[5] <= 3528) { //if closer then 2 ft right
			stop();
			left();
			sleep(1);
			stop();

		}
		if (backSensor[5] <= 3528) { //if closer then 2 ft back
			stop();
			forward();
			sleep(1);
			stop();

		}

		forward();

	}
}
