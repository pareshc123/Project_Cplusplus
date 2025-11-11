/*
	Basic of functions in C++
*/

#include <iostream>
#include "math.h"

using namespace std;

int main() {
	int num1, num2, sum;
	cout << "Enter two numbers: ";
	cin >> num1 >> num2;
	// call the function
	sum = add(num1, num2);
	cout << "The sum is: " << sum << endl;
	return 0;
}
