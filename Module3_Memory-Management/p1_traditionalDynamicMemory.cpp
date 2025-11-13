/*
	Traditiional Way to allocate memory in C++ using malloc() function
	
	In C and C++, malloc() is a function that allocates raw memory from the heap.
		void* malloc(size_t size);

	Notice the return type — it returns a void*.
	That means:
		- malloc() gives you a pointer to a memory block,
	      but it doesn’t know what type of data you’ll store there — so it gives you a generic pointer (void*)
	
	In C this is not a problem, as C allows implicit conversion from void* to any other pointer type.
	
	However, in C++ you must explicitly cast the void* to the desired pointer type.
	Otherwise, you’ll get a compiler error: 
		"error: cannot convert 'void*' to 'int*' in initialization"

	Type Casting means to convert a variable from one data type to another explicitly.
	For example:

	1. Simple Type casting conversion:
		double pi = 3.14;
		int n = (int)pi;   // type casting double -> int

	2. Type cast conversion for pointers (to allocate memory for an integer in C++):
		int* p = (int*)malloc(sizeof(int));  // Explicit cast required in C++
		
		- Here, we cast the void* returned by malloc to int* to indicate that p is a pointer to an integer.
		- sizeof(int) ensures the correct number of bytes are allocated for an integer on any system.

*/

#include <iostream>
#include <cstdlib>  // malloc() and free() are declared in <cstdlib>

using namespace std;

int memoryAllocationInteger(int& x);
int memoryAllocationArray(int& arr);

int main() {

	cout << "--- Memory Allocation using malloc() in C++ ---" << endl;

	cout << "\n1. Memory Allocation for a single Integer:" << endl;
	int intVar;
	int intReturn = memoryAllocationInteger(intVar);

	if (intReturn == 0) {
		cout << "Memory allocation for single integer was successful." << endl;
	}
	else {
		cout << "Memory allocation for single integer failed." << endl;
	}

	cout << "\n2. Memory Allocation for an Array of Integers:" << endl;
	int arrVar;
	int arrReturn = memoryAllocationArray(arrVar);
	if (arrReturn == 0) {
		cout << "\nMemory allocation for integer array was successful." << endl;
	} else {
		cout << "\nMemory allocation for integer array failed." << endl;
	}
	
	return 0;
}


int memoryAllocationInteger(int& x) {

	// Allocate memory for one integer using malloc -- Explicit cast required in C++
	int* mptr = (int*)malloc(sizeof(int));

	// Always check if allocation was successful
	if (mptr == nullptr) {
		cout << "Memory Allocation Failed" << endl;
		return 1;
	}

	// Initialize the allocated memory
	*mptr = 10;
	cout << "Value stored at allocated memory (heap) " << mptr << " is: " << *mptr << endl;

	// Free the allocated memory (return it to the heap)
	free(mptr);

	// After freeing, make pointer NULL to avoid dangling pointer
	mptr = nullptr;

	return 0;
}

int memoryAllocationArray(int& arr) {

	// Allocate memory for an array of 5 integers using malloc
	int* arrPtr = (int*)malloc(5 * sizeof(int));

	// Always check if allocation was successful
	if (arrPtr == nullptr) {
		cout << "Memory Allocation Failed" << endl;
		return -1;
	}

	// Initialize the allocated array
	for( int i =0; i < 5; i++) {
		arrPtr[i] = i + 1;  // Assign values 1 to 5
	}

	// Print the values in the allocated array
	cout << "Values in the allocated array: ";
	for( int i =0; i < 5; i++) {
		cout << arrPtr[i] << " ";
	}

	// Free the allocated memory (return it to the heap)
	free(arrPtr);

	// After freeing, make pointer NULL to avoid dangling pointer
	arrPtr = nullptr;

	return 0;
}
