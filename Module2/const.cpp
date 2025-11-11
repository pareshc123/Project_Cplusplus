/*
	Constants in C++

	syntax: const data_type VARIABLE_NAME = value;

*/

#include <iostream>

using namespace std;

int main() {

	// Define a constant variable
	const int DAYS_IN_WEEK = 7;
	cout << "Days in a week: " << DAYS_IN_WEEK << endl;
	
	// DAYS_IN_WEEK = 8; // Error: cannot modify a constant variable

	return 0;

}