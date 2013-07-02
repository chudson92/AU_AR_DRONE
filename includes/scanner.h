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
int waitforpin3(int pin, int level, int timeout);
void scan4me(int pointer, int pulsewidth[][3]);

#ifdef __cplusplus
}
#endif


#endif /* SONAR_H_ */
