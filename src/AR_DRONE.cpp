//============================================================================
// Name        : AR_DRONE.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================



#include <stdio.h>
#include <stdlib.h>

#include <signal.h>
#include <string>
#include <string.h>
#include <sys/wait.h>
#include <iostream>
#include <sstream>

#include <unistd.h>//this is what you need for fork, pipe, exec
#include "diagnostics.h"




int main(){

	diagnostics();


/*
	//try to create our pipe for use later
	int myPipe[2];
	if(pipe(myPipe) == -1)
	{
		perror("Pipe");
		exit(1);
	}



	//char *binName = "echo";
	char *message = "takeoff()\n";
	char *message2 = "land()\n";

	//construct our strings to send
	//std::string myStr = std::string("hello");

	//fork our process
	int pid;
	pid = fork();

	if(pid == 0)//this is the child process
	{
		//we're redirecting STDIN such that it comes from the pipe
		//close standard in
		close(STDIN_FILENO);

		close(myPipe[1]);//close end of pipe your not using

		//duplicate our stdin as the pipe output
		dup2(myPipe[0], STDIN_FILENO);


		//change path
		chdir("/home/pi/Node_ws");

		//run new program
		system("node repl.js");

		//you would probably want to use one form of exec instead of system here.
		//exec executes a binary, so you just give it the path to the binary

		//http://www.gnu.org/software/libc/manual/html_node/Executing-a-File.html#Executing-a-File


		//char *argv[1];
		//char *message2 = "hello";
		//argv[0] = binName;
		//argv[1] = message2;
		//execvp("echo",argv);

	}
	else //the parent process
	{

		close(myPipe[0]);//close end of pipe your not using

		//now when ever you write to myPipe[0] in the parent, the child
		//treats it like standard in, which is the same as typing in the terminal.

		//if you are having trouble with multiple writes, you may need to
		//add a newline to the end of each command

		//send out output over that there pipe
		write(myPipe[1], message, strlen(message));  //write takes a c string, which is a char array
		sleep(10);
		write(myPipe[1], message2, strlen(message2));  //write takes a c string, which is a char array



	}
	*/

}//main


