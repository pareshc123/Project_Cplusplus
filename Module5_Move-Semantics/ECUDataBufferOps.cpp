/*
	Contains definitions for operator overloading in ECU class
*/

#include "ECUDataBuffer.h"

ECUDataBuffer& ECUDataBuffer::operator+=(const CANFrame& frame) {

	// Add Frame to the list
	CANbufferList.push_back(frame);

	return *this;		// so you can chain: ecu += f1 += f2;
}

const CANFrame& ECUDataBuffer::operator[](size_t size) const {

	if (size >= CANbufferList.size()) {
		throw std::out_of_range("ECUDataBuffer: index out of range");
	}

	// Frames are stored in CANBufferList
	return CANbufferList[size];
}

std::ostream& operator<<(std::ostream& os, const ECUDataBuffer& buffer)
{
	os << "ECU Data Buffer (" << buffer.CANbufferList.size() << " frames):\n";

	for (size_t i = 0; i < buffer.CANbufferList.size(); ++i)
	{
		os << "  [" << i << "] "
			<< buffer[i].toString() << "\n";   // Using operator[] overloading instead of buffer.CANbufferList[i].tostring()
	}

	return os;
}



