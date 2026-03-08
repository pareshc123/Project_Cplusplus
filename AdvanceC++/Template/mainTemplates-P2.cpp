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


int main() {
	
	cout << "============ Exercise 1 - CAN Message Wrapper ============" << endl;
	cout << "Case 1 (lvalue): Copy Payload" << endl;
	std::array<uint8_t, 8> data = { 1,2,3,4,5,6,7,8 };
	CanMessage msg(0x123, data);

	cout << "Case 2 (rvalue): move payload" << endl;
	CanMessage msg(
		0x123,
		std::array<uint8_t, 8>{1, 2, 3, 4, 5, 6, 7, 8}
	);


	cout << "============ Exercise 2 - SOME/IP Payload Builder ============" << endl;
	cout << "Case 1 (lvalue): Copy Payload" << endl;
	Seralizer sData;
	sData.serilaize(data);

	cout << "Case 2 (rvalue): move payload" << endl;
	Seralizer sData;
	sData.serilaize(std::array<uint8_t, 8>{1, 2, 3, 4, 5, 6, 7, 8});
	

	cout << "============ Exercise 3 - Secure Key Wrapper ============" << endl;
	cout << "Case 1 (lvalue): Copy Payload" << endl;
	Seralizer sData;
	sData.serilaize(data);

	cout << "Case 2 (rvalue): move payload" << endl;
	Seralizer sData;
	sData.serilaize(std::array<uint8_t, 8>{1, 2, 3, 4, 5, 6, 7, 8});

	return 0;
}