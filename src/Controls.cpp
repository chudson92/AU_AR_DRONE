#include "nodelink.h"
extern "C" {
#include "client.h"
}
void takeoff() {
	char **cmd;
	cmd[0] = "takeoff()";
	tcp(1,cmd);
}

void land() {
	char **cmd;
	cmd[0] = "land()";
	tcp(1,cmd);
}

void forward() {
	char **cmd;
	cmd[0] = "front()";
	tcp(1,cmd);
}

void back() {
	char **cmd;
	cmd[0] = "back()";
	tcp(1,cmd);
}

void left() {
	char **cmd;
	cmd[0]= "left()";
	tcp(1,cmd);
}

void right() {
	char **cmd;
	cmd[0]= "right()";
	tcp(1,cmd);
}

void up() {
	char **cmd;
	cmd[0] = "up()";
	tcp(1,cmd);
}

void down() {
	char **cmd;
	cmd[0] = "down()";
	tcp(1,cmd);
}

void rotateClockwise() {
	char **cmd;
	cmd[0] = "clockwise()";
	tcp(1,cmd);
}

void rotateCounterClockwise() {
	char **cmd;
	cmd[0] = "counterClockwise()";
	tcp(1,cmd);
}

void stop() {
	char **cmd;
	cmd[0]  = "stop()";
	tcp(1,cmd);
}

