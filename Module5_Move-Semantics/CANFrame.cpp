#include "CANFrame.h"
#include <random>

/*
	This .cpp file contains the definitions (/Prototype) of CANFrame Funcitons
*/

// ---- Default constructor ----
CANFrame::CANFrame() : m_id(0), m_dlc(0), m_data{ 0 } {}

// ---- Parametrized Constructor ----
CANFrame::CANFrame(uint32_t id, uint8_t dlc, const array<uint8_t, 8>& data)
	: m_id(id), m_dlc(dlc <= 8 ? dlc : 8), m_data(data) {}

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

CANFrame CANFrame::generateRandomFrame()
{	
	static random_device rd;		// Hardware-based random number source (seed).
	static mt19937 gen(rd());      // Mersenne Twister generator, seeded with rd.

	// Use unsigned int instead of uint8_t (as uint_8 is typedef of unsigned char
	// not allowed as a template type for Uniform distribution)
	uniform_int_distribution<unsigned int> idDist(0x000, 0x7FF);
	uniform_int_distribution<unsigned int> dlcDist(0x0, 0x8);
	uniform_int_distribution<unsigned int> byteDist(0x00, 0xFF);

	// Generate and cast back the ID and DLC code
	uint32_t id = idDist(gen);
	uint8_t dlc = static_cast<uint8_t>(dlcDist(gen));

	// Generate random data bytes
	std::array<uint8_t, 8> data{};
	for (uint8_t i = 0; i < dlc; i++)
		data[i] = static_cast<uint8_t>(byteDist(gen));

	return CANFrame(id, dlc, data);
}

CANFrame CANFrame::generatePatternFrame()
{

	static uint32_t nextID = 0x100;
	static uint8_t nextDLC = 4;      // can be set between 0 to 8

	std::array<uint8_t, 8> data{};
	for (uint8_t i = 0; i < nextDLC; i++)
		data[i] = i;  // simple increasing pattern

	CANFrame frame(nextID, nextDLC, data);

	// Update for next call
	nextID = (nextID + 1) & 0x7FF;   // wrap within standard ID range
	nextDLC = (nextDLC + 1) % 9;     // cycles 0–8

	return frame;
}
