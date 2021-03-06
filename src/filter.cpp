#include "filter.h"
#include <unistd.h>
#include <stdlib.h>
#include <algorithm>


using namespace std;

void median_filter2d(double raw_Readings[][5], double medians[5]) {
	double temp;

	double top[3];
	double front[3];
	double back[3];
	double left[3];
	double right[3];
	int Length = 3;

	top[0] = raw_Readings[0][0];
	top[1] = raw_Readings[1][0];
	top[2] = raw_Readings[2][0];



	front[0] = raw_Readings[0][1];
	//cout << "raw front 1: " << raw_Readings[0][1] << endl;
	front[1] = raw_Readings[1][1];
	//cout << "raw front 2: " << raw_Readings[1][1] << endl;
	front[2] = raw_Readings[2][1];
	//cout << "raw front 3: " << raw_Readings[2][1] << endl;

	back[0] = raw_Readings[0][2];
	back[1] = raw_Readings[1][2];
	back[2] = raw_Readings[2][2];

	left[0] = raw_Readings[0][3];
	left[1] = raw_Readings[1][3];
	left[2] = raw_Readings[2][3];

	right[0] = raw_Readings[0][4];
	right[1] = raw_Readings[1][4];
	right[2] = raw_Readings[2][4];




	//cout << "not sorted: "<<front[0] << "\n"<< front[1] << "\n"<< front[2] << "\n" << endl;
	sort(top, top+3);
	sort(front, front+3);
	sort(back, back+3);
	sort(left, left+3);
	sort(right, right+3);
	//cout << "sorted "<<front[0] << "\n"<< front[1] << "\n"<< front[2] << "\n" << endl;

/*	for (int reading = 1; reading < Length; reading++) {
		for (int position = reading;
				(position > 0) && (top[position - 1] > top[position]);
				position--) {
			temp = top[position];
			top[position] = top[position - 1];
			top[position - 1] = temp;
		}
		for (int position = reading;
				(position > 0) && (front[position - 1] > front[position]);
				position--) {
			temp = front[position];
			front[position] = front[position - 1];
			front[position - 1] = temp;
		}
		for (int position = reading;
				(position > 0) && (back[position - 1] > back[position]);
				position--) {
			temp = back[position];
			back[position] = back[position - 1];
			back[position - 1] = temp;
		}
		for (int position = reading;
				(position > 0) && (left[position - 1] > left[position]);
				position--) {
			temp = left[position];
			left[position] = left[position - 1];
			left[position - 1] = temp;
		}
		for (int position = reading;
				(position > 0) && (right[position - 1] > right[position]);
				position--) {
			temp = right[position];
			right[position] = right[position - 1];
			right[position - 1] = temp;
		}
	}*/

// put sorted data into return array
	medians[0] = top[1];
	medians[1] = front[1];
	//cout << "median front: " << medians[1] << endl;
	medians[2] = back[1];
	medians[3] = left[1];
	medians[4] = right[1];

	return;
}
