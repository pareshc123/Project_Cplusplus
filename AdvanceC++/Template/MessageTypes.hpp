#include<cstdint>
#include<array>
#include<utility>

struct CANFrame {
	uint32_t id;
	uint8_t dlc;
	std::array<uint8_t, 8> payload;
};

class CANMessage {

	CANFrame frame;

public:
	template <typename T>
	CANMessage(uint32_t m_id, uint8_t m_dlc, T&& m_payload) 
		: frame{ m_id, m_dlc, std::forward<T>(m_pyload)}
	{

	}
};
