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

	int pulsewidth[5][3];
/*	for(int y = 0; y < 5; y++){
		pulsewidth[y] = new int[3];
	}*/
	int pointer = 0;

	scan4me(pointer,pulsewidth);
	pointer = (pointer+1)%3;
	scan4me(pointer,pulsewidth);
	pointer = (pointer+1)%3;
	scan4me(pointer,pulsewidth);
	pointer = (pointer+1)%3;

	cout << "1" << endl;
	takeoff();
/*	cout << "2" << endl;
	sleep(10);
	land();*/

	while (autonomous == true) {
		//cout << "IN WHILE LOOP" << endl;
		//char* str;
		//receive(str, 4);
		//cout << " AFTER RECIEVE " << endl;
		//int scanTimes = 5;

		//std::cout << "After SCANTIMES" << std::endl;

		scan4me(pointer,pulsewidth);
		//cout << topSensor[5] << endl;

/*		if (topSensor[2] <= 3528) { //if closer then 2 ft above
			stop();
			down();
			stop();

		}*/

		//TODO: Implement a protocal for going around
		if (pulsewidth[2][1] <= 3528) { //if closer then 2 ft front
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


}
}
