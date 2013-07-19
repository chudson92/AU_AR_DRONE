/*
 * UDP.h
 *
 *  Created on: Jul 12, 2013
 *      Author: chris
 */

#ifndef _UDP_H_
#define _UDP_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <fcntl.h>


#define NAVDATA_PORT         5554
#define AT_PORT         5556
#define NAVDATA_BUFFER_SIZE     2048
#define WIFI_MYKONOS_IP     "192.168.1.1"

static int seq= 0;
static char navdata_message[NAVDATA_BUFFER_SIZE];

static int     at_socket = -1,         //sendto
    navdata_socket = -1; //recvfrom
static int32_t drone_state = 0, sequenceNumber, visionFlag;

static struct navdata_demo {
	uint32_t ctrl_state, vbat_flying_percentage;
	float theta, phi, psi;
	int32_t altitude;
	float vx, vy, vz;
	uint32_t num_frames;
	float det11, det12, det13, det21, det22, det23, det31, det32, det33;
	float detx, dety, detz;
	uint32_t detection_tag_index;
	uint32_t detection_camera_type;
	float drone11, drone12, drone13, drone21, drone22, drone23, drone31, drone32, drone33;
	float dronex, droney, dronez;
} navdemoData;


static struct sockaddr_in
    pc_addr,   //INADDR_ANY
    drone_at,  //send at addr
    drone_nav, //send nav addr
    from;

static float forwardPower = -.15;
static float rotPower = -.5;
static float tilt_left = -.3;
static float tilt_right = .3;

void setup(void);
void navdata_write(char *command);
void navdata_read(void);
void get_Navdata_demo(void);
 void forward();
 void left();
 void right();
 void hover();
 void rotate();
 void land();
 void watchDog();
 void takeoff();
 void parse_checksum(int *_index);
 void parse_navdemo(int *_index);
 void getNextOption(int *_index);
 void parse_navdata();
 void calib_magneto();
 float getVx();
 float getVy();

#endif /* UDP_H_ */
