
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <pthread.h>

#include <wiringPi.h>

#define TIMEOUT 999 /* any value other than LOW or HIGH */

int pinwait(int pin, int level, int timeout) {
	struct timeval now, start;
	int done;
	long micros;

	gettimeofday(&start, NULL );

	micros = 0;

	done = 0;

	while (!done) {
		gettimeofday(&now, NULL );
		if (now.tv_sec > start.tv_sec)
			micros = 1000000L;
		else
			micros = 0;
		micros = micros + (now.tv_usec - start.tv_usec);

		if (micros > timeout)
			done = 1;

		if (digitalRead(pin) == level)
			done = 1;
	}
	return micros;
}

/*void goscan(int scans, int returns[]){
 int i;
 for(i=0;i<scans;i++){
 scan(scans, returns);
 goscan(scans-1, returns);
 }

 }*/

void scanSensors(int scanTimes, int topSensor[], int frontSensor[], int leftSensor[], int rightSensor[], int backSensor[]) {

	//top 0
	//front 1
	//left 2
	//right 3
	//back 4
	int TRIGGER_PIN[5] = { 18, 22, 17, 27, 23 };
	int ECHO_PIN[5] = { 18, 22, 17, 27, 23 };

/*	 pinMode(TRIGGER_PIN[0], OUTPUT);
	 pinMode(TRIGGER_PIN[0], INPUT);
	 pinMode(TRIGGER_PIN[1], OUTPUT);
	 pinMode(TRIGGER_PIN[1], INPUT);
	 pinMode(TRIGGER_PIN[2], OUTPUT);
	 pinMode(TRIGGER_PIN[2], INPUT);
	 pinMode(TRIGGER_PIN[3], OUTPUT);
	 pinMode(TRIGGER_PIN[3], INPUT);
	 pinMode(TRIGGER_PIN[4], OUTPUT);
	 pinMode(TRIGGER_PIN[4], INPUT);*/

	int pulsewidth;

	if (wiringPiSetupGpio() == -1) {

		fprintf(stderr, "Can't initialise wiringPi: %s\n", strerror(errno));
		return;
	}

	while (1) {
		/* trigger reading */

		int loop;
		for (loop = 0; loop < scanTimes; loop++) {
			int count;
			for (count = 0; count < 5; count++) {
				digitalWrite(TRIGGER_PIN[count], HIGH);
				pinwait(ECHO_PIN[count], TIMEOUT, 45000); /* wait 350 microseconds */
				digitalWrite(TRIGGER_PIN[count], LOW);

				/* wait for reading to start */
				pinwait(ECHO_PIN[count], HIGH, 45000); /* 350 ms timeout */

				if (digitalRead(ECHO_PIN[count]) == HIGH) {
					pulsewidth = pinwait(ECHO_PIN[count], LOW, 70000L); /* 60 ms timeout */

					if (digitalRead(ECHO_PIN[count]) == LOW) {
						/* valid reading code */
						switch (count) {
						case 0:
							printf("pulsewidth inside scanner: %d\n", pulsewidth);
							//printf("%d\n", loop);
							topSensor[loop] = pulsewidth;
							continue;
						case 1:
							frontSensor[loop] = pulsewidth;
							continue;
						case 2:
							leftSensor[loop] = pulsewidth;
							continue;
						case 3:
							rightSensor[loop] = pulsewidth;
							continue;
						case 4:
							backSensor[loop] = pulsewidth;
							continue;
						}

						//printf("%d, ", pulsewidth);
					} else {
						/* no object detected code */
						printf("echo tiimed out\n");
					}
				} else {
					/* sensor not firing code */
					continue;
				}

				//}
				printf("\n");
			}
		}

			break;
		}

		return;
	}

