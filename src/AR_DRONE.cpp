#include <stdio.h>
#include <stdlib.h>

#include <signal.h>
#include <string>
#include <string.h>
#include <sys/wait.h>
#include <iostream>
#include <sstream>
#include "xbee.h"
#include <unistd.h>								//this is what you need for fork, pipe, exec
#include "diagnostics.h"



int main(){
	bool dia = diagnostics();								//launch diagnostics

	//if diagnostics return true launch

	if(dia){
		std::cout<< "launch?" <<std::endl;

	}
	else
		exit(EXIT_FAILURE);
}


