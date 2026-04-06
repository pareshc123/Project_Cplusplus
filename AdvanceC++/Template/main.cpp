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


#include "MessageStack.hpp"

int main() {

	MessageStack<CANFrame, 64> canStack;

	CANFrame frame{ 0x123, 8, {1,2,3,4,5,6,7,8} };
	canStack.push(frame);

	MessageStack<DiagnosticMessage, 32> diagStack;

	DiagnosticMessage dmsg{ 0x27, {0x01, 0x02} };
	diagStack.push(dmsg);

	return 0;
}