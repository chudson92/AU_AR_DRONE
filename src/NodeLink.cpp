#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <signal.h>
#include <string>
#include <string.h>
#include <sys/wait.h>
#include <iostream>
#include <sstream>
#include "xbee.h"
#include <unistd.h>								//this is what you need for fork, pipe, exec
#include "diagnostics.h"
using namespace std;

void writeMsg(char* messageSend);
void readMsg(char* messageBack);
void readback(char* messageBack);

int myPipe[2];
int myPipe2[2];
int pid;

void cmd(char* messageSend, char* messageBack) {
//try to create our pipe for use later

	std::cout << "msg in cmd: " << messageSend << std::endl;
	if (pipe(myPipe) == -1) {
		perror("Pipe");
		exit(1);
	}

	/*if (pipe(myPipe2) == -1) {
		perror("Pipe");
		exit(1);
	}*/

	//char *binName = "echo";
/*	char *message = "takeoff()\n";
	char *message2 = "land()\n";
	char *message3 = "battery()\n";*/

	//construct our strings to send
	//std::string myStr = std::string("hello");

	//fork our process

	pid = fork();

	if (pid == 0) //this is the child process
			{

		//we're redirecting STDIN such that it comes from the pipe
		//close standard in
		close(STDIN_FILENO);
		//close(STDOUT_FILENO);
		//std::cout << "INSIDE CHILD PROCESS" << std::endl;
		close(myPipe[1]); //close end of pipe your not using
		//close(myPipe2[0]);

		//duplicate our stdin as the pipe output
		dup2(myPipe[0], STDIN_FILENO);
		//dup2(myPipe2[1], STDOUT_FILENO);

		//change path
		chdir("/home/pi/Node_ws");

		//std::cout << "LAUNCHing NODE.JS" << std::endl;
		//run new program
		system("node repl.js");
		sleep(1);
		//std::cout << "LAUNCHED NODE.JS" << std::endl;

	} else //the parent process
	{

		//system(" ps -ef | grep -w 'node repl.js' | cut -c10-15 | tail -2 | head -1");

		close(myPipe[0]); //close end of pipe your not using
		//close(myPipe2[1]);

		//char killmessage[2]; killmessage[0] = 3; killmessage[1] = 3;
		//write(myPipe[1], killmessage, 2);
		//writeMsg(messageSend);
		//sleep(2);
		readMsg(messageBack);
		//write(myPipe[1], messageSend, strlen(messageSend));
		//writeMsg(messageSend);

	//	messageBack = "true";
		return;
	}
}

void writeMsg(char* messageSent) {
	//cout << "SENDING MESSAGE " << messageSent << " INSIDE writeMsg" << endl;
	write(myPipe[1], messageSent, strlen(messageSent));
	return;

}

void readMsg(char* msgBack) {
	cout << "INSIDE READ MESSAGE" << endl;


	int i = 0;
	char* ptr;

	ptr = msgBack;
	msgBack[0] = 't';
	msgBack[1] = 'r';
	msgBack[2] = 'u';
	msgBack[3] = 'e';
/*	while (1) {

		if (read(myPipe2[0], ptr, 1) > 0) {
			cout << ptr << endl;
			ptr++;
			i++;
		}
		if (i == 16) {
			//kill(pid+2, SIGKILL);
			break;

		}
		cout << "FAILED TO BREAK OUT OF WHILE LOOP" << endl;
	}*/
	cout << " OUT OF WHILE LOOP" << endl;
	return;
}

