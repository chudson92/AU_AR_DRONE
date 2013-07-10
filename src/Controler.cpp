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
double lastMeasurement[5];

void controller() {

	cout << "running" << endl;
	while (1) {
		scanSonar(lastMeasurement);
		cout << lastMeasurement[1] << endl;

		if (lastMeasurement[1] < 0.003528) {
			cout << "------------------STOP------------------" << endl;
		}

	}
}
