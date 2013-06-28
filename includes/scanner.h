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
int scan(int scans, int returns[]);
void goscan(int scans, int returns[]);

#ifdef __cplusplus
}
#endif


#endif /* SONAR_H_ */
