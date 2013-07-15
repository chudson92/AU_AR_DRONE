#ifndef FILTER_H
#define FILTER_H

#include <iostream>

#define SIZE 11 // number of readings from each sonar


// filtering method: retrieves SIZE readings and returns median value
int* median_filter5(int[SIZE], int[SIZE], int[SIZE], int[SIZE], int[SIZE], int[5]);
void median_filter2d(double raw_Readings[3][5], double medians[5]);
int median_filter1(int[SIZE]);


#endif
