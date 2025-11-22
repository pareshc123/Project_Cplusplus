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

// Pipeline processing functions
int normalizeSensor(int v);
int filterNoise(int v);
int convertToVoltage(int v);
int processSensorPipeline(int value, int (*stage)(int));

// FSM states
void stateIdle();
void stateRun();
void stateError();

enum ECUState {
	IDLE,
	RUNNING,
	ERROR
};

// Next-state logic
ECUState nextState(ECUState s);


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

	//  ------  Exercise7: Sensor Processing Pipeline using Callback Function:  -------
	cout << "\nExercise7: Sensor Processing Pipeline using Callback Function:" << endl;
	
	int raw = 123;

	cout << "Input sensor: " << raw << endl;

	raw = processSensorPipeline(raw, normalizeSensor);
	raw = processSensorPipeline(raw, filterNoise);
	raw = processSensorPipeline(raw, convertToVoltage);

	cout << "Final processed value: " << raw << endl;

	//  ------  Exercise8: Finite State Machine (FSM) using Function Pointers:  -------
	cout << "\nExercise8: Finite State Machine (FSM) using Function Pointers:" << endl;

	void (*stateFunctions[3])() = {
		stateIdle,
		stateRun,
		stateError
	};

	ECUState current = IDLE;

	for (int i = 0; i < 3; i++) {
		stateFunctions[current]();
		current = nextState(current);
	}

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


// Pipeline processing functions
int normalizeSensor(int v) {
	cout << "  Normalizing...\n";
	return v / 10;
}
int filterNoise(int v) {
	cout << "  Filtering noise...\n";
	return v - 2;
}
int convertToVoltage(int v) {
	cout << "  Converting to voltage...\n";
	return v * 0.1;
}
int processSensorPipeline(int value, int (*stage)(int)) {  // Main pipeline executor
	return stage(value);
}

// FSM states
void stateIdle() {
	cout << "[STATE] IDLE\n";
}
void stateRun() {
	cout << "[STATE] RUNNING\n";
}
void stateError() {
	cout << "[STATE] ERROR\n";
}

// Next-state logic
ECUState nextState(ECUState s) {
	switch (s) {
	case IDLE:    return RUNNING;
	case RUNNING: return ERROR;
	case ERROR:   return ERROR;
	}
	return ERROR;
}
