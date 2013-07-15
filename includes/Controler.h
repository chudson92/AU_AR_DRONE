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

void  controller(int fd);


#endif /* CONTROLER_H_ */
