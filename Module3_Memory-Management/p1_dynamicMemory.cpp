/*

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

int main() {

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