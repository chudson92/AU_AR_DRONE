/*
 * XbeeIO.h
 *
 *  Created on: Jul 10, 2013
 *      Author: chris
 */

#ifndef _XBEEIO_H_
#define _XBEEIO_H_

//int updateIndex = 0; ///<To keep number of AU_UAV MAVLink messages
//int WPSendSeqNum = 0; ///<Int to keep up with number of wp's sent to UAV
//int myMessages[256]; ///< Array to keep up with which messages are sent

struct serialData {
	char data[100];
	bool start;
	bool received;
	int i;
	char startChar;
	char endChar;
	int fd;
};

typedef serialData SerialData;

bool setup_port(int fd, int baud, int data_bits, int stop_bits, bool parity, bool hardware_control);
int open_port(std::string& port);
void read_char(SerialData &myPacket);
void sendMsg(char* message);
void init_serialData(SerialData &d, char start, char end);
void read_quick(SerialData &myPacket);

#endif /* XBEEIO_H_ */
