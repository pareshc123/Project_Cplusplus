/*
	Declaration and Initialization

	Common types of Initialization in C++:
	1. Copy Initialization                 --> int myInt = 10; Assignment (=) operator --> should be avoided for user-defined types
	2. Direct Initialization               --> int myInt(10); should be avoided for user-defined types
	3. Uniform Initialization              --> int myInt{10}; preferred for all types --> Widely used in modern C++
	4. Default Initialization              --> int myInt; (uninitialized for built-in types, default constructor for user-defined types)
	5. Value Initialization                --> int myInt{}; (zero-initialized for built-in types, default constructor for user-defined types)
	6. Zero Initialization                 --> int myInt = 0; (explicitly set to zero)
	7. Aggregate Initialization            --> int myArray[5] = {1, 2, 3, 4, 5}; (for arrays and structs)
	8. List Initialization                 --> std::vector<int> myVector = {1, 2, 3, 4, 5}; (for STL containers)
	9. Dynamic Initialization              --> int* myIntPtr = new int(10); (for dynamic memory allocation)
	10. Constant Initialization            --> const int myConstInt = 10; (for constants)
	11. Reference Initialization           --> int& myRefInt = myInt; (for references)
	12. Brace-or-equal Initializer         --> int myInt = {10}; (combination of copy and uniform initialization)
	13. In-Class Member Initializer        --> class MyClass { int myInt{10}; }; (for class members)
	14. Nested Brace Initialization        --> int myArray[2][3] = { {1, 2, 3}, {4, 5, 6} }; (for multi-dimensional arrays)
	15. Implicit Conversion Initialization --> double myDouble = 10; (int to double conversion)
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