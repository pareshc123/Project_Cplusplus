#ifndef CANFRAME_H
#define CANFRAME_H

/*
	
	This is a C++ header file (.h) that defines a class called CANFrame.

	A CAN frame is a message sent on a CAN Bus (used in cars, ECUs, sensors, etc.).
	This class simply stores:
		- an ID (message identifier)
		- a DLC (data length = how many bytes)
		- an 8-byte data array

	This is a container for sending or receiving CAN messages.

	#include <cstdint>
	This header provides fixed-size integer types, like:
		uint8_t = unsigned 8-bit integer (0 to 255)
		uint32_t = unsigned 32-bit integer (0 to 4,294,967,295)
	These are very common in embedded / automotive, because you want exact size.

*/

#include <array>
#include <string>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

class CANFrame
{

private:

	uint32_t m_id;						// CAN Identifier	
	uint8_t m_dlc;                     // DLC (data length code) 0-8bytes
	array<uint8_t, 8> m_data{};		  // 8-byte payload

public:

	// ---- Constructors ----
	CANFrame();
	CANFrame(uint32_t id, uint8_t dlc, const array<uint8_t, 8>& data);

	// ---- Getters ---- 
	uint32_t getID() const;
	uint8_t getDLC() const;
	const array<uint8_t,8>& getdata() const;

	// ---- Setters ---- 
	void setID(uint32_t id);
	void setDLC(uint32_t dlc);
	void setDATA(const array<uint8_t,8>& data);

	// ---- Utility Function to print the CAN Frame ---- 
	string toString() const;

	// ---- Random CANFrame Generator ---- 
	static CANFrame generateRandomFrame();

	// ---- Pattern Based generator ---- 
	static CANFrame generatePatternFrame();

	// ---- Destructors ---- 
	~CANFrame();

};

#endif
