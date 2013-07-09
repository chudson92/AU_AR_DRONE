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
#include "scan.h"

}

using namespace std;
double lastMeasurement[5] = {-1.0, -1.0, -1.0, -1.0, -1.0};



void controller() {

	cout << "1" << endl;

	int micros[1] = {-1};
	scanSonar(lastMeasurement);

	while (1) {
		double lastMeasurement[5] = {-1.0, -1.0, -1.0, -1.0, -1.0};
		cout << "IN WHILE LOOP" << endl;
		scanSonar(lastMeasurement);
		cout << "returned value :  " << micros[0] << endl;
		

	/*	if (topSensor[2] <= 3528) { //if closer then 2 ft above
			stop();
			down();
			stop();

		}*/

		//TODO: Implement a protocal for going around
		/*if (micros[0] <= 3528) { //if closer then 2 ft front
			stop();

			land();

		}
		/*if (leftSensor[2] <= 100) { //if closer then 2 ft left
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

		}*/
		//forward();

}
}
