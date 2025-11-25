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

void printBuffer(const Temperature* buffer, int size);

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
	const int SIZE = 5;
	Temperature tempBuffer[SIZE];
	Temperature* tempBufferPtr = tempBuffer;

	for (int i = 0; i < 7; ++i) {
		tempBufferPtr->value = static_cast<float>(1.23f*rand() / 100) + i;
		tempBufferPtr->timestamp_ms = 1000 + 100 * i;

		tempBufferPtr++;

		if (tempBufferPtr == tempBuffer + SIZE) {           // 
			tempBufferPtr = tempBuffer;                    // go back to start
		}

		printBuffer(tempBuffer, SIZE);

	}


	//  ------  Exercise3: Dynamic Allocation of Struct:  -------
	cout << "\nExercise3: Dynamic Allocation of Struct" << endl;


	//  ------  Exercise4: Array of Structs + Pointer Traversal:  -------
	cout << "\nExercise4: Array of Structs + Pointer Traversal" << endl;


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

void printBuffer(const Temperature* buffer, int size) {

	cout << " Buffer content (memory order):\n";

	const Temperature* tempPtr = buffer;

	for (int i = 0; i < size; ++i) {
		cout << "  Value: " << tempPtr->value << ", TimeStamp: " << tempPtr->timestamp_ms << endl;
		tempPtr++;
	}

}