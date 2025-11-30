/*
	This is the main file. It will
		create several CAN frames using CANFrame Class
		push them into the container
		call overloaded operators to do some operations
		print results
*/

#include "CANFrame.h"

// Print CAN Frame
string CANFrame::toString() const
{
	ostringstream oss;
	oss << "ID: 0x" << hex << uppercase << m_id
		<< " DLC: " << dec << static_cast<int>(m_dlc)
		<< " Data: ";

	for (size_t i = 0; i < m_dlc; ++i)
	{
		oss << hex << setw(2) << setfill('0')
			<< static_cast<int>(m_data[i]) << " ";
	}

	return oss.str();
}

// Compare CAN Frame
bool CANFrame::operator==(const CANFrame& other) const {      // Equality

	return (m_id == other.m_id && m_dlc == other.m_dlc && m_data == other.m_data);
}

bool CANFrame::operator!=(const CANFrame& other) const {     // Inequality

	return !(*this == other);
}

// Sort CANFrame
bool CANFrame::operator<(const CANFrame& other) const {

	return m_id < other.m_id;
}

// Access DataByte from CAN Frame
uint8_t CANFrame::operator[](size_t index) const {

	if (index >= m_dlc) {

		throw std::out_of_range("CANFrame: Data index out of range");
	}

	return m_data[index];
}