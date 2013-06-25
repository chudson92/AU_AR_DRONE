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

void cmd(char* messageBack) {
//try to create our pipe for use later
	int myPipe[2];
	if (pipe(myPipe) == -1) {
		perror("Pipe");
		exit(1);
	}

	int myPipe2[2];
	if (pipe(myPipe2) == -1) {
		perror("Pipe");
		exit(1);
	}

	//char *binName = "echo";
	char *message = "takeoff()\n";
	char *message2 = "land()\n";
	char *message3 = "battery()\n";


	//construct our strings to send
	//std::string myStr = std::string("hello");

	//fork our process
	int pid;
	pid = fork();

	if (pid == 0) //this is the child process
			{
		//we're redirecting STDIN such that it comes from the pipe
		//close standard in
		close (STDIN_FILENO);
		close (STDOUT_FILENO);

		close(myPipe[1]); //close end of pipe your not using
		close(myPipe2[0]);

		//duplicate our stdin as the pipe output
		dup2(myPipe[0], STDIN_FILENO);
		dup2(myPipe2[1], STDOUT_FILENO);

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

	} else //the parent process
	{

		close(myPipe[0]); //close end of pipe your not using
		close(myPipe2[1]);
		//now when ever you write to myPipe[0] in the parent, the child
		//treats it like standard in, which is the same as typing in the terminal.

		//if you are having trouble with multiple writes, you may need to
		//add a newline to the end of each command

		//send out output over that there pipe
		//write(myPipe[1], message, strlen(message)); //write takes a c string, which is a char array
		//sleep(10);
		//write(myPipe[1], message2, strlen(message2)); //write takes a c string, which is a char array
		//char messageBack[15];
		//std::cout << message3 << std::endl;
		write(myPipe[1], message3, strlen(message3));
		//std::cout << "hello" << std::endl;
		//sleep(5);
		//read(myPipe2[0], messageBack, 15 );
	//	int
		int i = 0;
		char* ptr;

		ptr = messageBack;
		messageBack[17] = '\0';
		while (1) {


			if (read(myPipe2[0], ptr, 1) > 0) {
				ptr++;
				i++;
			}
			if (i == 17) {
				 kill(pid+2, SIGKILL);
				break;
			}



	}
		//std::cout << "message end of nodelink.cpp" << messageBack << std::endl;
	}

	//std::cout << "PID = " << pid << std::endl;

}
