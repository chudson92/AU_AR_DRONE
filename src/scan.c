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

double lastMeasurement[5];
double risingEdge[5];
int previousState[5];
int currentState[5];
double StartTime = 0.0;

struct timespec start[5], now[5];

double Now();

/***********************************************************************\
* Input    : None                                                       *
* Output   : Returns the current system time                            *
\***********************************************************************/
double Now(){
  struct timeval tv_CurrentTime;
  gettimeofday(&tv_CurrentTime,NULL);
  return( (double) tv_CurrentTime.tv_sec + (double) tv_CurrentTime.tv_usec / 1000000.0-StartTime);
}


void scanSonar(double lastMeasurement[5]) {
	sleep(.25);
	StartTime = Now();

/*	pinMode(ECHO_PIN[0], OUTPUT);
	pinMode(ECHO_PIN[1], OUTPUT);
	pinMode(ECHO_PIN[2], OUTPUT);
	pinMode(ECHO_PIN[3], OUTPUT);
	pinMode(ECHO_PIN[4], OUTPUT);*/

	if (wiringPiSetupGpio() == -1) {

		fprintf(stderr, "Can't initialise wiringPi: %s\n", strerror(errno));
	}

	//double lastMeasurement[5] = { -1.0, -1.0,  -1.0, -1.0, -1.0 };
	double risingEdge[5] = {  -1.0, -1.0,  -1.0, -1.0, -1.0};

	int count = 0;
	int i;
	float currentTime;

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

