#ifndef ECUDATABUFFER_H
#define ECUDATABUFFER_H

#include <cstddef>  // for size_t
#include "CANFrame.h"
#include <vector>

class ECUDataBuffer {

private:
	int* dataPtr;		// pointer to dynamically allocated CAN data buffer
	size_t size;    // number of CAN data elements to be stored

	// The ECU stores a list of incoming CAN frames in a container
	std::vector<CANFrame> CANbufferList;

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

	// Operator Overloading function declaration
	ECUDataBuffer& operator+=(const CANFrame& frame);       // Add a CAN frame to ECU buffer
	const CANFrame& operator[](size_t index) const;			// Access stored CAN frames
	friend std::ostream& operator<<(std::ostream& os, const ECUDataBuffer& buffer);   // << (friend) to print the whole buffer
	
	// Destructor
	~ECUDataBuffer();
};

#endif