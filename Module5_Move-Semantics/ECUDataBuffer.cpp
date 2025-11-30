#include <iostream>
#include "ECUDataBuffer.h"

using namespace std;

// Default Constructor
ECUDataBuffer::ECUDataBuffer() : size(0) {
	
	/*
		Example usage:
		ECUDataFrame ecu1;
	*/
	
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

	/*
		Example usage:
		ECUDataFrame ecu2(500);
	*/

	if (size > 0) {
		dataPtr = new int[size];    // an array of size
	}
	else {
		dataPtr = nullptr;
	}

	cout << "Parametrized constructor was called for creating a buffer of size " << size << endl;

}

// Copy constructor: when pointers are involved 
ECUDataBuffer::ECUDataBuffer(const ECUDataBuffer& other) : size(other.size) {

	/*
		When pointers are involved (Rule of 5 must be followed) 
		This constructor does the follwoing in order: 
				--> 1. allocate new momeory --> 2.deep copy the values
		
		Example usage:
		ECUDataFrame ecu3 = ecu2;
	*/

	cout << "[Copy Constructor] Deep copying buffer initiated ..." << endl;

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
ECUDataBuffer::ECUDataBuffer(ECUDataBuffer&& other) noexcept : dataPtr(other.dataPtr), size(other.size) {

	/*
		When pointers are involved (Rule of 5 must be followed) 
		This constructor does the follwoing in order: 
				--> 1. do not delete old memory --> 2. do not allocate new momeory --> 3. steal the values
		
		Example usage:
		
		// Function that returns a temporary (R-value) (must be implemented to get the R-Value)
		ECUDataBuffer generateTempBuffer()
		{
			ECUDataBuffer temp(1000);  // large temporary buffer
			return temp;               // returns an R-value (temporary) --> triggers MOVE
		}

		ECUDataFrame ecu4 = generateTempBuffer()
	*/

	cout << "[Move Constructor] Stealing buffer from temporary initiated ..." << endl;

	// Leave the source in a safe state
	other.dataPtr = nullptr;
	other.size = 0;
	
}

// Copy Assignment: when pointers are involved 
ECUDataBuffer& ECUDataBuffer::operator=(const ECUDataBuffer& other) {

	/*
		When pointers are involved (Rule of 5 must be followed) 
		This constructor does the follwoing in order: 
				--> 1. delete old memory --> 2. allocate new momeory --> 2. deep copy the values
		
		Example usage:
		ecu2 = ecu1;
	*/

	cout << "[Copy Assignment] Copying buffer ..." << endl;

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
		cout << "[nCopy Assignment] failed, both objects are same. Provide two different objects" << endl;
	}
	return *this;

}

// Move Assignment:  
ECUDataBuffer& ECUDataBuffer::operator=(ECUDataBuffer&& other) noexcept {

	/*
		When pointers are involved (Rule of 5 must be followed) 
		This constructor does the follwoing in order: 
				--> 1. delete old memory --> 2. steal the momory --> 2. clear others
		
		Example usage:
		
		// Function that returns a temporary (R-value) (must be implemented to get the R-Value)
		ECUDataBuffer generateTempBuffer()
		{
			ECUDataBuffer temp(1000);  // large temporary buffer
			return temp;               // returns an R-value (temporary) --> triggers MOVE
		}

		ecu5 = generateTempBuffer()
	*/

	cout << "[Move Assignment] Moving buffer ..." << endl;

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
		cout << "[Move Assignment] failed, both objects are same. Provide two different objects" << endl;
	}
	
	return *this;

}

int ECUDataBuffer::GetPtrValue() const
{
	cout << "Getting the buffer size for ---" << this << endl;

	if (dataPtr)
		return *dataPtr;
	else
		return 0; // or some default value/error handling
}

void ECUDataBuffer::SetPtrValue(size_t s)
{
	cout << "Setting the new buffer size for ---" << this << endl;
	cout << "Previous buffer size: " << size << ". Pointer points to: " << dataPtr << endl;

	// set the new value and then modify the existing pointer
	size = s;

	delete[] dataPtr;// free old buffer
	dataPtr = nullptr;

	// allocate a new buffer and initialize it to zero
	if (size > 0) {
		dataPtr = new int[size]();   // () is basically a initializer and sets the value ot zero [0,0,0 ...,0]
	}
	else {
		dataPtr = nullptr;
	}
	
	cout << "New Buffer size: " << size << ". Pointer points to: " << dataPtr << endl;

}

// Destructor
ECUDataBuffer::~ECUDataBuffer()
{
	cout << "[Destructor] Releasing buffer of size " << size << endl;
	delete[] dataPtr;
}