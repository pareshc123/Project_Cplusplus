/*
	Declaration and Initialization
*/

#include <iostream>

int main() {
	
	// scalar types
	int myInt = 10;               // integer
	int myIntZero{ 0 };          // integer initialized to zero --> Uniform initialization
	int myNegativeInt = -5;     // negative integer
	float myFloat = 3.14f;      // floating-point number
	double myDouble = 2.71828; // double-precision floating-point number
	char myChar = 'A';         // character

	// boolean type
	bool myBool = true;        // boolean value --> true or false / 1 or 0

	// Vector type
	int arr[5]; // only declaration of an array of integers

	int myArray[5] = { 1, 2, 3, 4, 5 }; // array of integers -- Declaration and Initialization

	// Output the values to verify
	std::cout << "Show the Scalar types: " << std::endl;
	std::cout << "Integer: " << myInt << std::endl;
	std::cout << "Zero Integer: " << myIntZero << std::endl;

	std::cout << "\nShow the Boolean: " << std::endl;
	std::cout << "Boolean: " << myBool << std::endl;

	std::cout << "\nShow the Vector type array: " << std::endl; // Requires loop to display array elements
	for (int i =0; i < 5; i++) {
		std::cout << "Element " << i << ": " << myArray[i] << std::endl;
	}

	return 0;
}