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



int waitforpin3(int pin, int level, int timeout)
{
   struct timeval now, start;
   int done;
   long micros;

   gettimeofday(&start, NULL);

   micros = 0;

   done=0;

   while (!done)
   {
      gettimeofday(&now, NULL);
      if (now.tv_sec > start.tv_sec) micros = 1000000L; else micros = 0;
      micros = micros + (now.tv_usec - start.tv_usec);

      if (micros > timeout) done=1;

      if (digitalRead(pin) == level) done = 1;
   }
   return micros;
}

void scan4me(int pointer, int pulsewidth[5][3]) {

	/*
	 *
	 * int myArray[10];
	 * int* myArray = new int[10];
	 * delete* myArray;
	 */


	int TRIGGER_PIN[5] ={ 18, 17, 27, 22, 23 };
	int ECHO_PIN[5] = { 18, 17, 27, 22, 23 };

	   pinMode(TRIGGER_PIN[0], OUTPUT);
	   pinMode(TRIGGER_PIN[0], INPUT);
	   pinMode(TRIGGER_PIN[1], OUTPUT);
	   pinMode(TRIGGER_PIN[1], INPUT);
	   pinMode(TRIGGER_PIN[2], OUTPUT);
	   pinMode(TRIGGER_PIN[2], INPUT);
	   pinMode(TRIGGER_PIN[3], OUTPUT);
	   pinMode(TRIGGER_PIN[3], INPUT);
	   pinMode(TRIGGER_PIN[4], OUTPUT);
	   pinMode(TRIGGER_PIN[4], INPUT);


	   if (wiringPiSetupGpio () == -1)
	   {

	      fprintf (stderr, "Can't initialize wiringPi: %s\n", strerror (errno)) ;
	      return ;
	   }

	int done = 0;


	while (!done) {

		int i;
		for (i = 0; i < 5; i++) {
			digitalWrite(TRIGGER_PIN[i], HIGH);
			waitforpin3(ECHO_PIN[i], TIMEOUT, 50000);
			digitalWrite(TRIGGER_PIN[i], LOW);
			int j;

				waitforpin3(ECHO_PIN[i], HIGH, 50000);
				if (digitalRead(ECHO_PIN[i]) == HIGH)
					pulsewidth[i][pointer] = waitforpin3(ECHO_PIN[i], LOW, 50000L);

		}
		done = 1;

/*	int p;
	   for ( p = 0; p < 5; p++) {
		   int q;
	        for (q = 0; q < 1; q++) {
	            printf("%d \n", pulsewidth[p][q]);
	        }
	        printf("\n");
	   }*/
	}
	} /* 60 ms timeout */
