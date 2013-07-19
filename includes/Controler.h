/*
 * Controler.h
 *
 *  Created on: Jun 27, 2013
 *      Author: chris
 */

#ifndef _CONTROLER_H_
#define _CONTROLER_H_


#include "XbeeIO.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "filter.h"
extern "C" {
#include "scan.h"
#include "UDP.h"
}

/*The controller is were any that needs to be run during flight should be included.
 * It is here that UDP Packets are configured, sent to and received from the Drone.
 * See UDP.c for more information on Packets.
 * We populate our buffer in the controller with 3 readings from scan.c prior to takeoff()
 * See Scan.c for more details.
 * The drone must receive a message from the Drone every 100ms or it believes it has lost connection.
 * */
void  controller(int fd);


#endif /* CONTROLER_H_ */
