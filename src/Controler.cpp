/*
 * Controler.cpp
 *
 *  Created on: Jun 27, 2013
 *      Author: chris
 */

#include "Controler.h"
#include <iostream>
using namespace std;
double lastMeasurement[5];


void controller(int fd) {

	SerialData myPacket3;
	double medians[5];
    myPacket3.start = true;
    myPacket3.received = false;
    myPacket3.i = 0;
    myPacket3.startChar = '#';
    myPacket3.endChar = '!';
	myPacket3.fd = fd;
	int pointer = 0;
	double readings[3][5];
	int i;
	for(i = 0; i < 3 ; i++){
	scanSonar(lastMeasurement);	
	int j;
	for(j =0; j < 5; j++){
		readings[i][j] = lastMeasurement[j];
}
	cout << "\n" ;
}

	median_filter2d(readings,medians);


	//takeoff();

	setup();
	while (1) {
		get_Navdata_demo();


		read_quick(myPacket3);
		if(myPacket3.received == true){
			hover();
			land();
			break;

		}
		scanSonar(lastMeasurement);
		int k;
		for(k =0; k < 5; k++){
			readings[pointer][k] = lastMeasurement[k];

	}
		pointer = (pointer + 1)%3;
		median_filter2d(readings,medians);

		if(medians[1] <= .003528 ){
			cout << "if:" << medians[1] << endl;
			hover();
			watchDog();
			cout << " --------------OBJECT DETECTED --------------" << endl;

		}

		navdata_read();


	}

}
