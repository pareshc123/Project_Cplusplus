#ifndef ECUDATABUFFER_H
#define ECUDATABUFFER_H

#include <cstddef>  // for size_t

class ECUDataBuffer {

private:
	int* dataPtr;		// pointer to dynamically allocated CAN data buffer
	size_t size;    // number of CAN data elements to be stored

public:

	// Constructors
	ECUDataBuffer();									  // default
	ECUDataBuffer(size_t s);							 // parametrized
	ECUDataBuffer(const ECUDataBuffer& other);			// Copy constructor
	ECUDataBuffer(ECUDataBuffer&& other) noexcept;     // Move Constructor

	// Assignment Operators
	ECUDataBuffer& operator=(const ECUDataBuffer& other);		 // Copy Assignment
	ECUDataBuffer& operator=(ECUDataBuffer&& other) noexcept;   // Move Assignment 

	// Getters and Setters
	int GetPtrValue() const;
	void SetPtrValue(size_t s);

	// Destructor
	~ECUDataBuffer();  
};

#endif