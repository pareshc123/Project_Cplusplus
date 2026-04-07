/*
	
	Perfect forwarding: 
		Perfect forwarding preserves the original value category (lvalue/rvalue) when passing arguments to another function.

	we use std::forward
	template<typename T1, typename T2>
	Employee(T1&& name, T2&& id)
		: m_Name{std::forward<T1>(name)},
		  m_Id{std::forward<T2>(id)}
	{}
	
	Now behaviour becomes:

	Argument type	           Result
	------------------------------------------
		lvalue			forwarded as lvalue
		rvalue			forwarded as rvalue
	
	Perfect forwarding ensures:
		copy when needed
		move when possible

*/

#include<iostream>
#include<cstdint>
#include<array>
#include<vector>
#include<utility>
#include<string>

using std::cout;
using std::endl;


// Exercise 1
struct CanFrame {
	uint32_t id;
	std::array<uint8_t, 8> data;
};


class CanMessage {

	CanFrame frame;

public:
	template<typename T>
	CanMessage(uint32_t id, T&& payload)
		: frame{ id, std::forward<T>(payload) }
	{
	}
};


// Exericse 2
struct Payload {
	std::vector<uint8_t> buffer;          // Ethernet payloads can be large, so vector is acceptable
};

class Seralizer {

public:
	template<typename T>
	static Payload serilaize(T&& data) {
		Payload p;
		p.buffer = std::forward<T>(data);
		return p;
	}

};


// Exercise 3
class SecureKey {

	/*
	Without forwarding --> temporary key -> copy into object (2 key copies in RAM)
	Bad for Security, --> perfect forwarding ensures, move key
	*/

private:
	std::vector<uint8_t> sKey;

public:
	template<typename T>
	SecureKey(T&& key)
	{
		auto&& k = std::forward<T>(key);
		sKey = std::vector<uint8_t>(k.begin(), k.end());
	}
};


// Exercise 4
struct DiagnosticMessage {
	uint8_t serviceID;
	std::vector<uint8_t> payload;
};

template<typename T>
DiagnosticMessage createMessage(uint8_t sid, T&& payload) {

	return DiagnosticMessage{ sid, std::forward<T>(payload) };
}


// Exericse 5: Variadic template
class EventPublisher
{
public:

	// public API used by application
	template<typename... Args>
	void publish(Args&&... args)
	{
		std::cout << "Publishing event...\n";

		// forward arguments to internal send function
		send(std::forward<Args>(args)...);
	}

private:

	// simulate network sending
	template<typename... Args>
	void send(Args&&... args)
	{
		std::vector<uint8_t> networkBuffer;

		// fold expression packs arguments
		(append(networkBuffer, std::forward<Args>(args)), ...);

		std::cout << "Event sent. Payload size: "
			<< networkBuffer.size()
			<< " bytes\n";
	}

	// append integer data
	void append(std::vector<uint8_t>& buffer, uint32_t value)
	{
		buffer.push_back(value & 0xFF);
		buffer.push_back((value >> 8) & 0xFF);
		buffer.push_back((value >> 16) & 0xFF);
		buffer.push_back((value >> 24) & 0xFF);
	}

	// append string data
	void append(std::vector<uint8_t>& buffer, const std::string& str)
	{
		buffer.insert(buffer.end(), str.begin(), str.end());
	}

	// append raw byte payload
	void append(std::vector<uint8_t>& buffer, const std::vector<uint8_t>& payload)
	{
		buffer.insert(buffer.end(), payload.begin(), payload.end());
	}
};



int main() {
	
	cout << "============ Exercise 1 - CAN Message Wrapper ============" << endl;
	cout << "Case 1 (lvalue): Copy Payload" << endl;
	std::array<uint8_t, 8> data = { 1,2,3,4,5,6,7,8 };
	CanMessage msg(0x123, data);

	cout << "Case 2 (rvalue): move payload" << endl;
	CanMessage msg1(
		0x123,
		std::array<uint8_t, 8>{1, 2, 3, 4, 5, 6, 7, 8}
	);


	cout << "\n============ Exercise 2 - SOME/IP Payload Builder ============" << endl;
	cout << "Case 1 (lvalue): Copy Payload" << endl;
	std::vector<uint8_t> v(data.begin(), data.end());         // array to vector
	Seralizer::serilaize(v);

	cout << "Case 2 (rvalue): move payload" << endl;
	Seralizer::serilaize(std::vector<uint8_t>{1, 2, 3, 4, 5, 6, 7, 8});
	

	cout << "\n============ Exercise 3 - Secure Key Wrapper ============" << endl;
	cout << "Case 1 (lvalue): Copy Key" << endl;
	std::string secKey{ "54s!H&as5#" };
	SecureKey sec(secKey);

	cout << "Case 2 (rvalue): move temp key" << endl;
	SecureKey secM(std::string("54s!!%6s^45"));


	cout << "\n============ Exercise 4 - Diagnostic Message Factory ============" << endl;
	std::cout << "Case 1: lvalue payload (copy)\n";

	std::vector<uint8_t> existingPayload{ 0x01, 0x02, 0x03 };

	DiagnosticMessage udsmsg = createMessage(0x10, existingPayload);

	std::cout << "Payload size: " << udsmsg.payload.size() << std::endl;
	std::cout << "Original payload size: " << existingPayload.size() << std::endl;

	std::cout << "\nCase 2: rvalue payload (move)\n";

	DiagnosticMessage msg2 =
		createMessage(0x22, std::vector<uint8_t>{0xAA, 0xBB, 0xCC});

	std::cout << "Payload size: " << msg2.payload.size() << std::endl;


	cout << "\n============ Exercise 5 - ECU Event Publisher ============" << endl;
	EventPublisher publisher;

	std::cout << "===== Example 5.1: Sensor Event =====\n";

	uint32_t timestamp = 100123;
	std::string sensorName = "WheelSpeed";
	std::vector<uint8_t> sensorPayload{ 0x11, 0x22, 0x33 };

	publisher.publish(timestamp, sensorName, sensorPayload);

	std::cout << "\n===== Example 5.2: Temporary Payload =====\n";

	publisher.publish(
		200555,
		std::string("EngineTemp"),
		std::vector<uint8_t>{0xAA, 0xBB}
	);

	return 0;
}