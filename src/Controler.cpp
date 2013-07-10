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

void controller(int fd) {

	cout << "running" << endl;

	SerialData myPacket3;
//	init_serialData(myPacket3, '#', '!');

    myPacket3.start = true;
    myPacket3.received = false;
    myPacket3.i = 0;
    myPacket3.startChar = '#';
    myPacket3.endChar = '!';
	myPacket3.fd = fd;

	takeoff();
	int block = 0;
	while (1) {
		cout << "In while loop" << endl;
		read_quick(myPacket3);
		//cout << myPacket3.data << endl;
		if(myPacket3.received == true){
			cout << "AHHHHHHHHHHHHHHHHHHHHHH LAND!" << endl;
			land();
			sleep(1);
			break;
		}
		cout << "at sonar" << endl;
		scanSonar(lastMeasurement);
//		cout << lastMeasurement[1] << endl;

		if(block == 0){
	//	forward();
		}

		if (lastMeasurement[1] < 0.003528) {
			stop();
			//back();
			//sleep(1);
			//stop();
			//block = 1;
		}
		if(lastMeasurement[0] < .001500){
		}

	}
	cout << "BOOOOOM I CRASHED" << endl;
	land();
}
