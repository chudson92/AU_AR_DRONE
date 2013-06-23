/*
 * sonar.h
 *
 *  Created on: Jun 21, 2013
 *      Author: chris
 */

#ifndef SONAR_H_
#define SONAR_H_

#ifdef __cplusplus
extern "C" {
#endif
int waitforpin(int pin, int level, int timeout);
int ping();
#ifdef __cplusplus
}
#endif


#endif /* SONAR_H_ */
