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


int waitforpin(int pin, int level, int timeout)
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

int ping()
{
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
   printf("testing...\n");
   int pulsewidth;

   if (wiringPiSetupGpio () == -1)
   {
    printf("testingerror...\n");
      fprintf (stderr, "Can't initialise wiringPi: %s\n", strerror (errno)) ;
      return 1 ;
   }


   while (1)
   {
      /* trigger reading */

		int loop;
		for(loop = 0; loop < 1 ; loop++){
		int count;
		for(count = 0;count < 5 ;count++){
		digitalWrite(TRIGGER_PIN[count], HIGH);
		waitforpin(ECHO_PIN[count], TIMEOUT, 45000); /* wait 350 microseconds */
		digitalWrite(TRIGGER_PIN[count], LOW);

      /* wait for reading to start */
      waitforpin(ECHO_PIN[count], HIGH, 45000); /* 350 ms timeout */

      if (digitalRead(ECHO_PIN[count])  == HIGH)
      {
         pulsewidth = waitforpin(ECHO_PIN[count], LOW, 70000L); /* 60 ms timeout */

         if (digitalRead(ECHO_PIN[count]) == LOW)
         {
            /* valid reading code */
        	return pulsewidth;
            //printf("%d, ", pulsewidth);
         }
         else
         {
            /* no object detected code */
            printf("echo tiimed out\n");
         }
      }
      else
      {
         /* sensor not firing code */
         printf("error, ");
      }

   }
                   printf("\n");
 }

 break;
}
   return 1;
}
