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
	while (autonomous == true) {
		char* str;
		receive(str, 4);
		int scans[5];
		//goscan(1,scans); //scan 1 time
		scans[0] = 1; //top
		scans[1] = 2; //front
		scans[2] = 3; //left
		scans[3] = 4; //right
		scans[4] = 5; //back

		if (scans[0] <= 3528) { //if closer then 2 ft above
			stop();
			down();
			sleep(1);
			stop();

		}

		//TODO: Implement a protocal for going around
		if (scans[1] <= 3528) { //if closer then 2 ft front
			stop();
			back();
			sleep(1);
			stop();

		}
		if (scans[2] <= 3528) { //if closer then 2 ft left
			stop();
			right();
			sleep(1);
			stop();

		}
		if (scans[3] <= 3528) { //if closer then 2 ft right
			stop();
			left();
			sleep(1);
			stop();

		}
		if (scans[4] <= 3528) { //if closer then 2 ft back
			stop();
			forward();
			sleep(1);
			stop();

		}

		forward();

	}
}
