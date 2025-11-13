/*
	Modern Dynamic Memory in C++
	
	In modern C++, the preferred way to allocate dynamic memory is by using the new and delete operators.
	
	new operator allocates memory and returns a pointer of the appropriate type.
	delete operator frees the allocated memory.

	syntax for new:

		1. Allocate memory for a single integer
			int* p = new int;  // No explicit cast needed -- new allocates and return int*
			*p = 10;
			         OR
			int* p = new int(10);  // Allocates and initializes to 10

		2. Allocate memory for an array of integers
			int* arr = new int[5];  // Allocates an array of 5 integers
			for(int i = 0; i < 5; i++) arr[i] = i + 1;

	syntax for delete:

		1. Free memory allocated for a single integer
			delete p;
		
		2. Free memory allocated for an array of integers
			delete[] arr;

	Note: 		
		- Always check if the pointer returned by new is not null (in low memory situations).
		- After deleting, set the pointer to nullptr to avoid dangling pointers.

	Important Difference between malloc/free and new/delete:
		- malloc/free are C-style memory management functions and do not call constructors/destructors.
		- new/delete are C++ operators that call constructors/destructors, making them suitable for C++ objects.

*/

#include <iostream>

using namespace std;

void New();
void NewArrays();
void Strings();

int main() {

	cout << "--- Memory Allocation using new in C++ ---" << endl;

	New();
	NewArrays();
	Strings();

	// End of Program
	return 0;
}

void New() {

	cout << "\n--- Memory Allocation using new for interger ---" << endl;

	// Allocate memory for a single integer using new
	int* p = new int;

	// Always check if allocation was successful
	if (p == nullptr) {
		cout << "Memory Allocation Failed" << endl;
		return;
	}

	// Initialize the allocated memory
	*p = 10;

	cout << "Value of allocated integer: " << *p << endl;
	
	// Free the allocated memory
	delete p;

	// Avoid dangling pointer
	p = nullptr;  
	cout << "Memory for single integer freed successfully." << endl;		
}

void NewArrays() {

	cout << "\n--- Memory Allocation using new for Array ---" << endl;

	// Allocate memory for an array of integers using new
	int size = 5;

	int* arrPtr = new int[5];

	// Always check if allocation was successful
	if(arrPtr == nullptr) {
		cout << "Memory Allocation for array Failed" << endl;
		return;
	}

	// Initialize the allocated array
	for (int i = 0; i < size; i++) {
		arrPtr[i] = i + 1;

	}

	cout << "Values in allocated integer array: ";
	for (int i = 0; i < size; i++) {
		cout << arrPtr[i] << " ";
	}

	cout << endl;

	// Free the allocated memory for the array
	delete[] arrPtr;

	arrPtr = nullptr;  // Avoid dangling pointer

	cout << "Memory for integer array freed successfully." << endl;

}

void Strings() {

	cout << "\n--- Memory Allocation using new for String ---" << endl;

	char* str = new char[4];

	strcpy_s(str, 4, "C++"); // note: use strcpy_s for safety (avoid bufferflow) and allocate one extra byte for null terminator

	cout << str << endl;

	delete[] str;
}