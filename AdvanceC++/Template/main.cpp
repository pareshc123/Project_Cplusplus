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

// function pointer
void customCANValidator(const CANFrame& msg) {
	if (msg.id == 0) {
		std::cout << "Invalid CAN ID !\n";
	}
}

// function object --> Functor
struct CANValidatorFunctor {
	void operator()(const CANFrame& msg) {
		if (msg.id == 0) {
			std::cout << "Invalid CAN ID !\n";
		}
	}
};

int main() {

	// geneic way of defining message stack
	MessageStack<CANFrame, 64> canStack;

	CANFrame frame1{ 0x00, 8, {1,2,3,4,5,6,7,8} };
	// Static behavior
	canStack.push(frame1);

	// callback -> function pointer (check via callback fucntion)
	CANFrame invalid_frame1{ 0x00, 6, {1,2,3,4,5,8} };
	canStack.push(invalid_frame1, customCANValidator);

	// callback -> function pointer (check via Valiadtor.hpp)
	CANFrame invalid_frame2{ 0xff, 9, {1,2,3,4,5,6,7,8} };
	canStack.push(invalid_frame2, customCANValidator);

	// callback -> functor aka function object
	CANFrame frame2{ 0x22, 5, {1,2,3,7,8} };
	// CANValidatorFunctor canfunc;
	// canStack.push(frame2, canfunc);
	canStack.push(frame2, CANValidatorFunctor{});

	int count = 2;  // since we have already pushed 2 frames manually
	uint32_t filterID = 0x123;

	// implement lambda expression
	CANFrame frame3{ 0x123, 3, {1,4,8} };
	canStack.push(frame3, [&count, filterID](const CANFrame& frame) mutable {
		count++;
		if (frame.id == filterID) {
			std::cout << "Lambda: Important CAN ID!\n";
		}
	});

	// print the complete stack

	return 0;
}

/*
  below is just an example for other types, they will fail at static_assert() since diagnosticMessage
  and EthernetMessage has std::vector<>

MessageStack<DiagnosticMessage, 32> diagStack;

DiagnosticMessage dmsg{ 0x27, {0x01, 0x02} };
diagStack.push(dmsg);

// using alias
EthStack ethstack;
EthernetMessage ethmsg = { std::vector<uint8_t>{1, 2, 3, 4} };
ethstack.push(ethmsg);

// exampple of template alias
SmallStack<CANFrame> s1;
SmallStack<DiagnosticMessage> s2;

*/