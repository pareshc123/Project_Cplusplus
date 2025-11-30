/*
	Contains definitions for operator overloading in ECU class
*/

#include "ECUDataBuffer.h"

ECUDataBuffer& ECUDataBuffer::operator+=(const CANFrame& frame) {

	// Add Frame to the list
	CANbufferList.push_back(frame);
	
	cout << "CAN Frame Added, Current Buffer size: " << CANbufferList.size() << endl;

	return *this;		// so you can chain: ecu += f1 += f2;
}

const CANFrame& ECUDataBuffer::operator[](size_t size) const {

	if (size >= CANbufferList.size()) {
		throw std::out_of_range("ECUDataBuffer: index out of range");
	}

	// Frames are stored in CANBufferList
	return CANbufferList[size];
}

bool ECUDataBuffer::operator==(const ECUDataBuffer& other) const
{
    // Compare simple fields first
    if (size != other.size)
        return false;

    // Compare internal CAN buffer sizes
    if (CANbufferList.size() != other.CANbufferList.size())
        return false;

    // Compare each CAN frame using CANFrame::operator==
    for (size_t i = 0; i < CANbufferList.size(); ++i)
    {
        if (!(CANbufferList[i] == other.CANbufferList[i]))
            return false;
    }

    return true;
}

ECUDataBuffer ECUDataBuffer::operator+(const ECUDataBuffer& other) const
{
    ECUDataBuffer result;

    // Merge CAN frames from *this
    for (const auto& frame : CANbufferList)
        result.CANbufferList.push_back(frame);

    // Merge CAN frames from other
    for (const auto& frame : other.CANbufferList)
        result.CANbufferList.push_back(frame);

    // Update size field (not used much anymore)
    result.size = result.CANbufferList.size();

    return result;   // return by VALUE (safe)
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



