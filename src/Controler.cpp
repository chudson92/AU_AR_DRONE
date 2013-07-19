/*
 * Controler.cpp
 *
 *  Created on: Jun 27, 2013
 *      Author: chris
 */

#include "Controler.h"
#include <sys/time.h>
#include <iostream>
using namespace std;
double lastMeasurement[5];

#define right_buffer .0015
#define left_buffer .0015
#define forward_buffer .003
#define top_buffer .0033
#define back_buffer .0015

#define SET_FORWARD(i) (i |= 0x01)
#define SET_LEFT(i) (i |= 0x02)
#define SET_RIGHT(i) (i |= 0x04)

#define CLEAR_FORWARD(i) (i &= ~(0x01))
#define CLEAR_LEFT(i) (i &= ~(0x02))
#define CLEAR_RIGHT(i) (i &= ~(0x04))

#define FORWARD(i) (i & 0x01)
#define LEFT(i) (i & 0x02)
#define RIGHT(i) (i & 0x04)

void controller(int fd) {
	struct timeval difference, start, now;

	int forward_counter = 0;
	short consecutive = 0;
	uint8_t state = 0;
	printf("in controller");
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
	for (i = 0; i < 3; i++) {
		//printf("in forloop calling scan");
		scanSonar(lastMeasurement);
		int j;
		for (j = 0; j < 5; j++) {
			readings[i][j] = lastMeasurement[j];
		}
		cout << "\n";
	}

	median_filter2d(readings, medians);

	setup();
	watchDog();
	gettimeofday(&start, NULL);
	takeoff();
	sleep(1);
	watchDog();
	sleep(1);
	watchDog();
	//forward();
	//left();
	//calib_magneto();
	//sleep(4);
	//get_Navdata_demo();
	while (1) {
		//get_Navdata_demo();
		//hover();
		watchDog();
		read_quick(myPacket3);
		if (myPacket3.received == true) {
			hover();
			land();
			break;

		}
		scanSonar(lastMeasurement);
		int k;
		for (k = 0; k < 5; k++) {
			readings[pointer][k] = lastMeasurement[k];

		}
		pointer = (pointer + 1) % 3;
		median_filter2d(readings, medians);

		/*Avoidance*/
		//printf("for med: %f\n", medians[1]);
		if (medians[1] <= forward_buffer) {
			//printf("for med: %f\n", medians[1]);
			hover();
			printf("-----------OBJECT DETECTED---------\n");
			if (!FORWARD(state)) {
				if (consecutive) {
					forward_counter++;
					//printf("Forward COUNTER: %d\n",forward_counter );
				} else {
					forward_counter = 0;

					consecutive = 1;

					//printf("-----------FORWARD---------\n");
				}
				if (forward_counter == 5) {
					watchDog();
					hover();
					hover();
					hover();
					hover();
					hover();
					hover();
					sleep(2);
					land();

					return;
					//printf("-----------LAND---------\n");
				}
			} else {
				CLEAR_FORWARD(state);
				forward_counter = 0;
				consecutive = 1;
			}

		} else {
			if (consecutive) {
				consecutive = 0;
				printf("Forward COUNTER CLEARED!!!!!!!!!!!\n");
			}
			if (!FORWARD(state)) {
				//forward();
				SET_FORWARD(state);
				printf("Now going foward!\n");
			}
		}

		if (medians[4] <= right_buffer) {
			//printf("med right: %f\n", medians[4]);
			if (FORWARD(state)) {
				hover();
				//	printf("-----------HOVER---------\n");
				CLEAR_FORWARD(state);
			}
			if (!LEFT(state)) {
				//left();
				//	printf("-----------GOING LEFT---------\n");
				SET_LEFT(state);
			} else if (RIGHT(state)) {
				//left();
				//printf("-----------GOING LEFT---------\n");
				CLEAR_RIGHT(state);
				SET_LEFT(state);
			}
		}

		if (medians[3] <= left_buffer) {
			if (FORWARD(state)) {
				hover();
				//	printf("-----------HOVER---------\n");
				CLEAR_FORWARD(state);
			}
			if (!RIGHT(state)) {
				//right();
				//	printf("-----------GOING RIGHT---------\n");
				SET_RIGHT(state);
			} else if (LEFT(state)) {
				//right();
				//	printf("-----------GOING RIGHT---------\n");
				CLEAR_LEFT(state);
				SET_RIGHT(state);
			}
		}

		//watchDog();
		navdata_read();
		parse_navdata();
		float vx, vy, seconds;
		gettimeofday(&now, NULL);
		//printf("%f", Now());
		//printf("now: %d, %d\n", now.tv_sec, now.tv_usec);
		//sleep(.25);
		timersub(&now, &start, &difference);
		vx = getVx();
		vy = getVy();
		//printf ("seconds: %d\nuseconds: %d\nvx: %f\nvy: %f\n", difference.tv_sec, difference.tv_usec, vx, vy);
		gettimeofday(&start, NULL);
		//printf("start: %d, %d\n", start.tv_sec, start.tv_usec);
	}

}
