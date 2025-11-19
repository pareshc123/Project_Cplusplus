/*
	Geeks for Geeks: https://www.geeksforgeeks.org/cpp/function-pointer-in-cpp/
	function pointer: return_type (*FuncPtr) (parameter type, ....);  eg
*/

#include <iostream>
using namespace std;

const int a = 10;
const int b = 3;

// Function for multiplication:
int multiply(int a, int b);
int multiply();

// Function containing function pointer as parameter
void print(int(*funcPtr2)())
{
	cout << "The value of the product is: " << funcPtr2() << endl;
}

int main() {

	//  Function pointer used to call the function
	int (*funcPtr1) (int, int);       // declare a function pointer
	funcPtr1 = multiply;					// referencing

	int x{ 15 };
	int y{ 2 };

	// Function pointer used to call the function
	int prod = funcPtr1(x, y);
	cout << "The value of the product is: " << prod << endl;

	// Passing a function pointer as a parameter
	print(multiply);

	return 0;
}

int multiply(int a, int b) {

	return a * b;
}

int multiply() {

	return a * b;
}