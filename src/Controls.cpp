#include <cstring>
#include <iostream>
#include "nodelink.h"
extern "C" {
#include "client.h"
}

void takeoff() {
	std::cout << "a" << std::endl;
	char cmd[10];
	strcpy(cmd, "takeoff()");
	std::cout << cmd << std::endl;
	sendCommand(cmd);
	std::cout << "b" << std::endl;
}

void land() {
	char* cmd;
	cmd = "land()";
	sendCommand(cmd);
}

void forward() {
	char* cmd;
	cmd = "front()";
	sendCommand(cmd);
}

void back() {
	char* cmd;
	cmd = "back()";
	sendCommand(cmd);
}

void left() {
	char* cmd;
	cmd= "left()";
	sendCommand(cmd);
}

void right() {
	char* cmd;
	cmd= "right()";
	sendCommand(cmd);
}

void up() {
	char* cmd;
	cmd = "up()";
	sendCommand(cmd);
}

void down() {
	char* cmd;
	cmd = "down()";
	sendCommand(cmd);
}

void rotateClockwise() {
	char* cmd;
	cmd = "clockwise()";
	sendCommand(cmd);
}

void rotateCounterClockwise() {
	char* cmd;
	cmd = "counterClockwise()";
	sendCommand(cmd);
}

void stop() {
	char* cmd;
	cmd  = "stop()";
	sendCommand(cmd);
}

