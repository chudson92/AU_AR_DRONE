//============================================================================
// Name        : AU_AR_DRONE.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

extern "C" {
#include "sonar.h"
}



int diagnostics() {


	//Initialize sensors -> where am i? _> if top blocked refuse launch
	// Check Xbee link to laptop
	//Check Node.js running -> if not launch
	//get navdata
	//check battery -> return battery %



	std::cout << "Initializing Sonar..." << std::endl;
	sleep(2);
	int dist = ping();

	//1.5m clearance (59 inches) drone flies at 1m
	if(dist >= 8673){
		std::cout << "Sonar Initialized" << std::endl;
		std::cout << dist/147 << " inch clearance " << std::endl;
	}
	else{
		std::cout <<  " low clearance ... takeoff blocked " << std::endl;
	}



	return 0;
}
