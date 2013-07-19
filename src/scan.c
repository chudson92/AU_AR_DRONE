#include "scan.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <pthread.h>

#include <wiringPi.h>


int ECHO_PIN[5] = { 18, 17, 27, 22, 23 };

double risingEdge[5];
int previousState[5];
int currentState[5];
double StartTime = 0.0;

struct timespec start[5], now[5];


/***********************************************************************\
* Input    : None                                                       *
 * Output   : Returns the current system time                            *
 \***********************************************************************/
double Now() {
	struct timeval tv_CurrentTime;
	gettimeofday(&tv_CurrentTime, NULL );
	return ((double) tv_CurrentTime.tv_sec
			+ (double) tv_CurrentTime.tv_usec / 1000000.0 - StartTime);
}

void scanSonar(double lastMeasurement[]) {
	//printf("inside scanSoanr");
	StartTime = Now();

	lastMeasurement[0] = -1.0;
	lastMeasurement[1] = -1.0;
	lastMeasurement[2] = -1.0;
	lastMeasurement[3] = -1.0;
	lastMeasurement[4] = -1.0;
	double risingEdge[5] = { -1.0, -1.0, -1.0, -1.0, -1.0 };

	int count = 0;
	int i;

	while (count < 5) {
		for (i = 0; i < 5; i++) {
			if (lastMeasurement[i] < 0.0) {
				currentState[i] = digitalRead(ECHO_PIN[i]);
				if (risingEdge[i] < 0.0) { //no rising edge
					if (previousState[i] == 0) {
						if (currentState[i] == 1) {
							risingEdge[i] = Now();
						}
					} else {
						previousState[i] = currentState[i];
					}
				} else { //I have a rising edge
					if (currentState[i] == 0) {
						lastMeasurement[i] = Now() - risingEdge[i];
						count++;
					}
				}

			}

		}

	}
}

