#include "nodelink.h"

void takeoff() {
	char* cmd = "takeoff()\n";
	writeMsg(cmd);
}

void land() {
	char* cmd = "land()\n";
	writeMsg(cmd);
}

void forward() {
	char* cmd = "front(.1)\n";
	writeMsg(cmd);
}

void back() {
	char* cmd = "back(.3)\n";
	writeMsg(cmd);
}

void left() {
	char* cmd = "left(.3)\n";
	writeMsg(cmd);
}

void right() {
	char* cmd = "right(.3)\n";
	writeMsg(cmd);
}

void up() {
	char* cmd = "up(.3)\n";
	writeMsg(cmd);
}

void down() {
	char* cmd = "down(.3)\n";
	writeMsg(cmd);
}

void rotateClockwise() {
	char* cmd = "clockwise(.3)\n";
	writeMsg(cmd);
}

void rotateCounterClockwise() {
	char* cmd = "counterClockwise(.3)\n";
	writeMsg(cmd);
}

void stop() {
	char* cmd = "stop()\n";
	writeMsg(cmd);
}

