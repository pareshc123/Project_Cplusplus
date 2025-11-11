/*
	Basic of functions in C++
	Includes seperate header file for function declarations --> math.h
	Includes seperate source file for function definitions --> math.cpp
*/

// include necessary libraries
#include <iostream>
#include "math.h"

// use the standard namespace
using namespace std;

int main() {

	// variable declaration
	int num1, num2, sum, subtraction;

	// user input
	cout << "Enter two numbers: ";
	cin >> num1 >> num2;
	
	// call the add function
	sum = add(num1, num2);
	cout << "The sum is: " << sum << endl;

	// call the subtract function
	subtraction = subtract(num1, num2);
	cout << "The subtraction is: " << subtraction << endl;

	// End of the program
	return 0;
}
