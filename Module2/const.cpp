/*
	Constants in C++
	- Constant variables are variables whose values cannot be changed after they are initialized.
	- Basic syntax: const data_type VARIABLE_NAME = value;

	Const Qualifier with Pointers:
	1. Pointer to a constant value:
		The value being pointed to cannot be changed through the pointer, but pointer can point to another variable
		Syntax: const int* ptr = &variable;

	2. Constant pointer:
		The pointer itself cannot point to another variable, but the value being pointed to can be changed.
		Syntax: int* const ptr = &variable;

	3. Constant pointer to a constant value:
		Pointer that is both constant and points to a constant value
		Syntax: const int* const ptr = &variable;

	4. Constant with References:
		A constant (const) reference in C++ is a reference that does not allow modification of the value it refers to.
		Once a reference (const or not) is initialized, it cannot be changed to refer to another variable.
		Syntax: const int& ref = variable;

	Reading Pointer Declarations “Right to Left”:
	const int* ptr;    // ptr is a pointer to a constant int
	int* const ptr2;   // ptr2 is a constant pointer to int
	const int* const ptr3; // ptr3 is a constant pointer to a constant int

*/

#include <iostream>

using namespace std;

int main() {

	// Define a constant variable
	const int DAYS_IN_WEEK = 7;
	cout << "Days in a week: " << DAYS_IN_WEEK << endl;
	
	// DAYS_IN_WEEK = 8; // Error: cannot modify a constant variable

	// 1. Pointer to a constant value:
	int value1 = 10;
	const int* ptrToConst = &value1;
	cout << "\nValue pointed to by ptrToConst: " << *ptrToConst << endl;
	// *ptrToConst = 20; // Error: cannot modify the value being pointed to

	// 2. Constant pointer:
	int value2 = 30;
	int* const constPtr = &value2;

	cout << "\nValue pointed to by constPtr: " << *constPtr << endl;
	*constPtr = 40; // Allowed: modifying the value being pointed to
	cout << "New value pointed to by constPtr: " << *constPtr << endl;
	// constPtr = &value1; // Error: cannot change the address stored in a constant pointer

	// 3. Constant pointer to a constant value:
	int value3 = 50;
	const int* const constPtrToConst = &value3;
	cout << "\nValue pointed to by constPtrToConst: " << *constPtrToConst << endl;
	// *constPtrToConst = 60; // Error: cannot modify the value being pointed to
	// constPtrToConst = &value1; // Error: cannot change the address stored in a constant pointer

	// 4. Constant with References:
	int value4 = 70;
	const int& constRef = value4;
	cout << "\nValue referred to by constRef: " << constRef << endl;
	// constRef = 80; // Error: cannot modify the value through a constant reference
	
	// End of Program
	return 0;

}