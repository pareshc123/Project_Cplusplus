/*
	This program demonstrates the difference between passing parameters by reference and by pointer (address) in C++.

	The program defines two functions to swap the values of two integers: one using pointers and the other using references. 
	It then shows how the values of the variables change after each swap operation.

	Note:
		A simple swap function (pass by value) is not included here, as it would not modify the original variables in the main function.
		but it will be swap the variables within the function scope only.
*/

#include <iostream>

using namespace std;

// Function declarations:
void swapByValue(int x, int y); 
void swapByPointer(int* x, int* y);
void swapByReference(int& x, int& y);

int main() {

	// Declare and initialize two variables

	int a{ 10 };
	int b{ 20 };

	cout << "Before swapping:" << endl;
	cout << "a = " << a << ", b = " << b << endl;

	// Swap using references
	swapByReference(a, b); // pass by reference

	cout << "After swapping by References:" << endl;
	cout << "a = " << a << ", b = " << b << endl;

	// swap using addresses
	swapByPointer(&a, &b); // pass by address

	cout << "After swapping by Address:" << endl;
	cout << "a = " << a << ", b = " << b << endl;

	// End of Program
	return 0;
}

// Function to swap two integers using pass by value (does not modify original variables)
void swapByValue(int x, int y) {
	int temp = x;
	x = y;
	y = temp;
}

// Function to swap two integers using pointers
void swapByPointer(int* x, int* y) {

	int temp = *x;
	*x = *y;
	*y = temp;

}

// Function to swap two integers using references --> pass by reference
void swapByReference(int& x, int& y) {
	int temp = x;
	x = y;
	y = temp;
}