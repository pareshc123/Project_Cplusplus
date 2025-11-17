#include <iostream>
#include "ECUDataBuffer.h"

using namespace std;

// Default Constructor
ECUDataBuffer::ECUDataBuffer() : size(0) {
	
	if (size > 0) {
		dataPtr = new int[size];    // an array of size
	}
	else {
		dataPtr = nullptr;
	}

	cout << "Defualt constructor was called for creating a buffer of size " << size << endl;
}

// Parametrized Constructor
ECUDataBuffer::ECUDataBuffer(size_t s) : size(s) {

	if (size > 0) {
		dataPtr = new int[size];    // an array of size
	}
	else {
		dataPtr = nullptr;
	}

	cout << "Parametrized constructor was called for creating a buffer of size " << size << endl;

}

// Copy constructor: when pointers are involved 
// 1. allocate new momeory --> 2.deep copy the values
ECUDataBuffer::ECUDataBuffer(const ECUDataBuffer& other) : size(other.size) {

	cout << "\n[Copy Constructor] Deep copying buffer initiated ...";

	// deep copy for array pointer
	if (size > 0) {
		dataPtr = new int[size];                         // allocate new memory
		for (size_t i = 0; i < size; ++i) {
			dataPtr[i] = other.dataPtr[i];				// deep copy values
		}
	}
	else {
		dataPtr = nullptr;
	}

}

// Move Constructor: when pointers are involved 
// 1. do not delete old memory --> 2. do not allocate new momeory --> 3. steal the values
ECUDataBuffer::ECUDataBuffer(ECUDataBuffer&& other) noexcept : dataPtr(other.dataPtr), size(other.size) {

	cout << "\n[Move Constructor] Stealing buffer from temporary initiated ...";

	// Leave the source in a safe state
	other.dataPtr = nullptr;
	other.size = 0;
	
}

// Copy Assignment: when pointers are involved 
// 1. delete old memory --> 2. allocate new momeory --> 2. deep copy the values
ECUDataBuffer& ECUDataBuffer::operator=(const ECUDataBuffer& other) {

	cout << "\n[Copy Assignment] Copying buffer ...";

	// Self assignment check
	if (this != &other) {

		delete[] dataPtr;

		size = other.size;

		if (size > 0) {
			dataPtr = new int[size];
			for (size_t i = 0; i < size; ++i) {
				dataPtr[i] = other.dataPtr[i];
			}
		}
		else {
			dataPtr = nullptr;
		}

	}
	else {
		cout << "\n[nCopy Assignment] failed, both objects are same. Provide two different objects" << endl;
	}
	return *this;

}

// Move Assignment: when pointers are involved 
// 1. delete old memory --> 2. steal the momory --> 2. clear others
ECUDataBuffer& ECUDataBuffer::operator=(ECUDataBuffer&& other) noexcept {

	cout << "\n[Move Assignment] Moving buffer ...";

	if (this != &other) {

		delete[] dataPtr;

		// Steal data
		dataPtr = other.dataPtr;
		size = other.size;

		// Leave source empty
		other.dataPtr = nullptr;
		other.size = 0;

	}
	else {
		cout << "\n[Move Assignment] failed, both objects are same. Provide two different objects" << endl;
	}
	
	return *this;

}

// Destructor
ECUDataBuffer::~ECUDataBuffer()
{
	cout << "\n[Destructor] Releasing buffer of size " << size << endl;
	delete[] dataPtr;
}