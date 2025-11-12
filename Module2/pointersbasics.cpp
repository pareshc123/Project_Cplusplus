/*
	Pointers Basics in C++

	A pointer is a variable that stores the memory address of another variable.

	1. Pointer Declaration and Initialization
	   - Declaration: int* ptr;          // pointer declared but uninitialized
	   - Initialization: ptr = &var;     // assign address of var to ptr

	2. Getting the Address of a Variable
	   - Use the '&' operator to get the address of a variable.
	   
	3. Dereferencing Pointers
	   - Use the '*' operator to access or modify the value stored at the address.

	4. Null Pointers
	   - A null pointer points to nothing (no valid memory).
	   - Accessing a null pointer (read/write) leads to runtime errors.
*/

#include <iostream>
using namespace std;

int main() {

	// 1. Pointer Declaration and Initialization
	int var = 42;              // Normal integer variable
	int* intptr = &var;        // Pointer to integer, storing the address of var

	cout << "Value of var: " << var << endl;
	cout << "Address of var stored in intptr: " << intptr << endl; // Prints memory address

	// 2. Getting the Address of a Variable
	cout << "Address of var using & operator: " << &var << endl; // Same as above

	// 3. Dereferencing Pointers
	cout << "Value pointed to by intptr using * operator: " << *intptr << endl;

	// Modifying the value of var using the pointer
	*intptr = 100;
	cout << "New value of var after modifying through pointer: " << var << endl;

	// 4. Null Pointers
	int* nullPtr = nullptr; // Pointer initialized to nullptr (points to nothing)
	if (nullPtr == nullptr) {
		cout << "nullPtr is a null pointer." << endl;
	}

	return 0;
}
