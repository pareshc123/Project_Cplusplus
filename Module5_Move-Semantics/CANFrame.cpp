#include "CANFrame.h"

/*
	This .cpp file contains the definitions (/Prototype) of CANFrame Funcitons
*/

CANFrame::CANFrame()
{
}

CANFrame::CANFrame(uint32_t id, uint8_t dlc, array<uint8_t, 8>& data)
{
}

CANFrame::~CANFrame()
{
}

uint32_t CANFrame::getID() const
{
	return 0;
}

uint8_t CANFrame::getDLC() const
{
	return 0;
}

const array<uint8_t, 8>& CANFrame::getdata() const
{
	// TODO: insert return statement here
}

void CANFrame::setID(uint32_t id)
{
}

void CANFrame::setDLC(uint32_t dlc)
{
}

void CANFrame::setDATA(const array<uint8_t, 8>& data)
{
}
