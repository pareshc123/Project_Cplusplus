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

int main() {

	// End of Program
	return 0;
}


