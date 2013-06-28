/*
 * sonar.h
 *
 *  Created on: Jun 21, 2013
 *      Author: chris
 */

#ifndef SCANNER_H_
#define SCANNER_H_

#ifdef __cplusplus
extern "C" {
#endif
int waitforpin(int pin, int level, int timeout);
void scanSensors(int scanTimes, int topSensor[], int frontSensor[], int leftSensor[], int rightSensor[], int backSensor[]);

#ifdef __cplusplus
}
#endif


#endif /* SONAR_H_ */
