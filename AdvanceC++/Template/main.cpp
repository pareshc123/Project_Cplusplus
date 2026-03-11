/*
	
	Project: Generic Automotive Message Stack (ECU_Message_Framework)

	Goal: create a type-safe message stack for ECU communication that can store different types of automotive messages.
			basically: Create a generic ECU message processing framework.

			src/
			 |--- MessageTypes.hpp
			 |--- MessageStack.hpp
			 |--- Logger.hpp
			 |--- Serializer.hpp
			 |--- SecureBuffer.hpp
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

	MessageStack<int, 5> msg;
	return 0;
}