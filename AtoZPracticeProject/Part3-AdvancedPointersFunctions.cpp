/*
	
	Advanced Pointers Functions
	Simulating Real Time ECU behaviour

*/

#include <iostream>

// CAN ID Handler Table
void handleEngineMessage(int data);
void handleBrakeMessage(int data);
void handleSteeringMessage(int data);
void dispatchCANMessage(int id, int data, void (*handlers[])(int), int handlerCount);  // dispatcher

// UDS Service Handler table
void udsSessionControl();
void udsECUReset();
void udsReadDID();
void executeUDSService(unsigned char sid, void (*udsTable[256])());

using namespace std;

int main() {

	//  ------  Exercise5: CAN ID Handler Table (Basic Function pointer):  -------
	cout << "\nExercise5: CAN ID Handler Table using Function Pointers:" << endl;

	// Array of CAN handlers (simulate CAN IDs 0, 1, 2, 3)
	void (*CANHandlers[3])(int) = { handleEngineMessage, handleBrakeMessage, handleSteeringMessage};
	dispatchCANMessage(0, 1500, CANHandlers, 3);
	dispatchCANMessage(1, 42, CANHandlers, 3);
	dispatchCANMessage(2, 10, CANHandlers, 3);
	dispatchCANMessage(5, 99, CANHandlers, 3);   // invalid

	//  ------  Exercise6: UDS Diagnostic Service Table (Real ECU Logic):  -------
	cout << "\nExercise6: UDS Service Handler Table (Array of Function Pointer):" << endl;
	
	// Create a UDS table (an array)
	void (*udsTable[256])() = { nullptr };

	// Intsall Services
	udsTable[0x10] = udsSessionControl;
	udsTable[0x11] = udsECUReset;
	udsTable[0x2] = udsReadDID;

	executeUDSService(0x10, udsTable); // session
    executeUDSService(0x11, udsTable); // reset
    executeUDSService(0x22, udsTable); // read DID
    executeUDSService(0x99, udsTable); // unsupported

	// End of Program
	return 0;
}


// CAN handlers
void handleEngineMessage(int data) {
	cout << "[ENGINE] RPM received: " << data << endl;
}
void handleBrakeMessage(int data) {
	cout << "[BRAKE] Pressure received: " << data << endl;
}
void handleSteeringMessage(int data) {
	cout << "[STEERING] Angle received: " << data << endl;
}
void dispatchCANMessage(int id, int data, 
	void (*handlers[])(int), int handlerCount) {

	if (id < 0 || id >= handlerCount || handlers[id] == nullptr) {
		cout << "[Error] Invalid CAN ID: " << id << endl;
		return;
	}
	handlers[id](data);
}


// UDS Service Implementations
void udsSessionControl() {
	cout << "[UDS] Entering diagnostic session.\n";
}
void udsECUReset() {
	cout << "[UDS] ECU Reset Requested.\n";
}
void udsReadDID() {
	cout << "[UDS] Reading Data Identifier (DID)...\n";
}
void executeUDSService(unsigned char sid, void (*udsTable[256])()) {

	if (udsTable[sid] == nullptr) {
		cout << "[UDS] Service 0x" << hex << (int)sid
			<< " not supported.\n";
		return;
	}
	udsTable[sid]();
}