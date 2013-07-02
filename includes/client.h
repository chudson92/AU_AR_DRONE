/*
 * client.h
 *
 *  Created on: Jun 29, 2013
 *      Author: chris
 */

#ifndef CLIENT_H_
#define CLIENT_H_
#ifdef __cplusplus
extern "C" {
#endif

void tcp(int argc, char argv[2][100]);
void sendCommand(char* cmd);

#ifdef __cplusplus
}
#endif
#endif /* CLIENT_H_ */
