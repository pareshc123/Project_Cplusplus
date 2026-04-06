#pragma once
#include<cstdint>
#include<array>
#include<vector>
#include<utility>

// CAN  Message
struct CANFrame {
	uint32_t id;
	uint8_t dlc;
	std::array<uint8_t, 8> payload;
};

class CANMessage {

public:
	template <typename T>
	CANFrame createCANMessage(uint32_t m_id, uint8_t m_dlc, T&& payload) 
	{
		return CANFrame{ m_id, m_dlc, std::forward<T>(payload) };
	}
};


// Diagnostic message
struct DiagnosticMessage {
	uint8_t serviceID;
	std::vector<uint8_t> diagPayload;
};

template<typename T>
DiagnosticMessage createDiagMessage(uint8_t sid, T&& payload) {

	return DiagnosticMessage{ sid, std::forward<T>(payload) };
}

// ethernet payload
struct EthernetMessage {
	std::vector<uint8_t> ethPayload;
};

template<typename T>
EthernetMessage createEthernetMessage(T&& eth_payload) {

	return EthernetMessage{ std::forward<T>(eth_payload) };
}