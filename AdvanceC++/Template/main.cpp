/*
	
	Project: Generic Automotive Message Stack (ECU_Message_Framework)

	Goal: create a type-safe message stack for ECU communication that can store different types of automotive messages.
			basically: Create a generic ECU message processing framework.

			src/
			 |--- MessageTypes.hpp
			 |--- MessageStack.hpp
			 |--- MessageStack_specialized.hpp
			 |--- Logger.hpp
			 |--- Serializer.hpp
			 |--- SecureBuffer.hpp
			 |--- Validator.hpp
			 |___ main.cpp

	Think of something used internally in middleware supporting:
		CAN frames
		SOME/IP messages
		Diagnostic messages

	Protocols commonly used in ECUs include:
		Controller Area Network
		SOME/IP
		Unified Diagnostic Services

*/

#include<vector>
#include "MessageStack_specialized.hpp"
// #include "MessageStack.hpp"

// Message type alias
using EthStack = MessageStack<EthernetMessage, 128>;

// alias template
template<typename T>
using SmallStack = MessageStack<T, 16>;


void customCANValidator(const CANFrame& msg) {
	if (msg.id == 0) {
		std::cout << "Invalid CAN ID !\n";
	}
}

int main() {

	// geneic way of defining message stack
	MessageStack<CANFrame, 64> canStack;

	CANFrame frame{ 0x123, 8, {1,2,3,4,5,6,7,8} };
	canStack.push(frame);

	// callback -> function pointer
	canStack.push(frame, customCANValidator);

	//MessageStack<DiagnosticMessage, 32> diagStack;

	//DiagnosticMessage dmsg{ 0x27, {0x01, 0x02} };
	//diagStack.push(dmsg);

	//// using alias
	//EthStack ethstack;
	//EthernetMessage ethmsg = { std::vector<uint8_t>{1, 2, 3, 4} };
	//ethstack.push(ethmsg);

	// exampple of template alias
	SmallStack<CANFrame> s1;
	// SmallStack<DiagnosticMessage> s2;

	return 0;
}