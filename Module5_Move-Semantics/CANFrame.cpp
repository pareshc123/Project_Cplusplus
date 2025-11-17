#include "CANFrame.h"
#include <iostream>
#include <sstream>
#include <iomanip>

/*
	This .cpp file contains the definitions (/Prototype) of CANFrame Funcitons
*/

// ---- Default constructor ----
CANFrame::CANFrame() : m_id(0), m_dlc(0), m_data{ 0 } {}

// ---- Parametrized Constructor ----
CANFrame::CANFrame(uint32_t id, uint8_t dlc, array<uint8_t, 8>& data)
	: m_id(id), m_dlc(dlc <= 8 ? dlc : 8), m_data(data) {}

// Destructor
CANFrame::~CANFrame()
{
	cout << "Destructor was called for CANFrame (ID: " << m_id << ")." << endl;
}

// ---- Getters ----
uint32_t CANFrame::getID() const
{
	return m_id;
}

uint8_t CANFrame::getDLC() const
{
	return m_dlc;
}

const array<uint8_t, 8>& CANFrame::getdata() const
{
	return m_data;
}

// ---- Setters ----
void CANFrame::setID(uint32_t id)
{
	m_id = id;
}

void CANFrame::setDLC(uint32_t dlc)
{
	m_dlc = (dlc <= 8 ? dlc : 8);
}

void CANFrame::setDATA(const array<uint8_t, 8>& data)
{
	m_data = data;
}

string CANFrame::toString() const
{
	std::ostringstream oss;
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

//CANFrame CANFrame::generateRandomFrame()
//{	
//
//	return CANFrame();
//}
//
//CANFrame CANFrame::generatePatternFrame()
//{
//
//	return CANFrame();
//}
