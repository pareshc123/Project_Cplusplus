#include <cstdint>
#include <iostream>

using namespace std;

// Exercise 1
struct CANFrame {
	uint32_t id;
	uint8_t  dlc;
	uint8_t  data[8];
};

CANFrame* getFrameById(CANFrame* buffer, int size, uint32_t id);


// Exercise 2
struct Temperature {
	float value;
	uint32_t timestamp_ms;
};

void printBuffer(const Temperature* buffer, int size, int validCount);


// Exercise 3
class ECU {
public:
	int id;
	float voltage;

	void printStatus() const {
		cout << "ECU ID: " << id << ", Voltage: " << voltage << " V" << endl;
	}
};

// Function to print all ECUs using pointer arithmetic
void printAll(const ECU* ptr, int size) {
	for (int i = 0; i < size; i++) {
		(ptr + i)->printStatus();   // call member function via pointer
	}
}

// Function to update voltage of an ECU via pointer
void updateVoltage(ECU* e, float newVoltage) {
	e->voltage = newVoltage;
}


// Exercise 4
float* getFuelRow(float (*map)[3], int rowIndex) {
	return *(map + rowIndex);
}

int main() {

	//  ------  Exercise1: CAN Frame Buffer Using Struct Pointers:  -------
	cout << "\nExercise1: CAN Frame Buffer Using Struct Pointers" << endl;

	// 1. Create CAN buffer of 10 frames(static array)
	CANFrame canBuffer[10] = {
	{100, 3, {1, 2, 3}},
	{200, 2, {10, 20}},
	{300, 8, {9, 8, 7, 6, 5, 4, 3, 2}},
	{400, 1, {99}},
	{500, 4, {5, 5, 5, 5}},
	{600, 8, {11,22,33,44,55,66,77,88}},
	{700, 0, {}},
	{800, 1, {55}},
	{900, 3, {7, 7, 7}},
	{1000, 8, {1,2,3,4,5,6,7,8}}
	};

	// 2. Search for a frame by ID
	uint32_t id = 300;
	CANFrame* resultPtr = getFrameById(canBuffer, 10, id);

	// 3. Handle nullptr safely
	if (resultPtr == nullptr) {
		cout << "Frame with ID: " << id << " not found." << endl;
		return 0;
	}

	// 4. Print using POINTER OPERATORS ONLY
	cout << "Frame found:\n";
	cout << "ID: " << resultPtr->id << "\n";
	cout << "DLC: " << static_cast<int>(resultPtr->dlc) << "\n";
	cout << "Data: ";

	// print all data bytes using pointer arithmetic only
	for (int i = 0; i < resultPtr->dlc; i++) {
		cout << static_cast<int>(*(resultPtr->data + i)) << " ";
	}
	cout << endl;

	//  ------  Exercise2: Sensor Buffer (Circular Buffer Simulation):  -------
	cout << "\nExercise2: Sensor Buffer (Circular Buffer Simulation)" << endl;
	
	// 1. Fixed array of 5 temperature samples
	int validCount = 0;                  // how many samples are valid
	const int SIZE = 5;
	Temperature tempBuffer[SIZE];
	Temperature* tempBufferPtr = tempBuffer;

	for (int i = 0; i < 7; ++i) {
		tempBufferPtr->value = static_cast<float>(1.23f*rand() / 100) + i;
		tempBufferPtr->timestamp_ms = 1000 + 100 * i;

		tempBufferPtr++;

		if (tempBufferPtr == tempBuffer + SIZE) {            
			tempBufferPtr = tempBuffer;                    // go back to start
			validCount = SIZE;
		}

		// Increase valid sample count (max = SIZE)
		if (validCount < SIZE) {
			validCount++;
		}

		printBuffer(tempBuffer, SIZE, validCount);

	}


	//  ------  Exercise3: ECU Object + Pointer to Method:  -------
	cout << "\nExercise3: ECU Object + Pointer to Method" << endl;
	// 1. Create array of 3 ECU objects
	ECU ecus[3] = {
		{101, 12.5},
		{102, 13.2},
		{103, 11.8}
	};

	cout << "Initial ECU Status:" << endl;
	printAll(ecus, 3);

	// 2. Update voltage of ECU[1] via pointer
	updateVoltage(&ecus[1], 14.0);

	cout << "\nAfter updating ECU[1] voltage:" << endl;
	printAll(ecus, 3);

	//  ------  Exercise4: Lookup Table (Calibration Table):  -------
	cout << "\nExercise4: Lookup Table (Calibration Table)" << endl;

	float fuelMap[3][3] = {
		{5.1f, 6.2f, 7.0f},   // RPM 1000
		{5.5f, 6.8f, 7.5f},   // RPM 2000
		{6.0f, 7.0f, 8.0f}    // RPM 3000
	};

	float* rowPtr = getFuelRow(fuelMap, 1);    // row 1 (RPM = 2000)

	for (int i = 0; i < 3; ++i) {
		cout << *(rowPtr + i) << " ";
	}

	cout << endl;

	// End of Program
	return 0;
}

CANFrame* getFrameById(CANFrame* buffer, int size, uint32_t id) {

	for (int i = 0; i < size; ++i) {
		CANFrame* ptr = buffer + i;

		if (ptr->id == id) {
			return ptr;
		}
	}

	return nullptr;           // no match found
}

void printBuffer(const Temperature* buffer, int size, int validCount) {

	cout << " Buffer content (memory order):\n";

	const Temperature* tempPtr = buffer;

	for (int i = 0; i < validCount; ++i) {
		cout << "  Value: " << tempPtr->value << ", TimeStamp: " << tempPtr->timestamp_ms << endl;
		tempPtr++;
	}

}