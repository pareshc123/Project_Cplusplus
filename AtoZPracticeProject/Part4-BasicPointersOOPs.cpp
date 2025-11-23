/*

	Part 4 - Pointers + Structs / Classes

		Pointer to an object
		The arrow operator (->)
		Dynamic allocation (new, delete) — only for understanding
		Object lifetime (stack vs heap)
		Pointers to arrays of objects
		Pointer to member variables
		Pointer to member functions (automotive-relevant)

		eg:
		struct SensorData {
			int id;
			float value;
		};

		SensorData tempSensor {101, 36.7f};                // Create an object

		SensorData* ptr = &tempSensor;                    // Take a pointer to that object:
		
		Now:
			ptr stores the address of tempSensor
			*ptr gives you the actual object
			ptr->field is simply syntactic sugar for dereferencing + accessing.
				ptr->id    // same as (*ptr).id		
				ptr->value // same as (*ptr).value

		when we use new & delete, we assign a block in memory (specifically in heap)
		we must delete it or else there will be memory leak, undefined behaviour etc

		hence we should use stack memory allocation (hence assign memory, delete is everything is taken care by the compiler)

		Stack allocation: SensorData s1; // automatic lifetime  --> receommended
		Heap allocation: SensorData* s2 = new SensorData; // must delete!  --> dangerous

*/

#include <iostream>
using namespace std;

struct Sensor {
	int id;
	float reading;
};

void printSensor(const Sensor* s);    // function pointer as an argument

Sensor* getMaxReading(Sensor* ptr, int size);

class ECU {
public:
	int id;
	void printID() {
		cout << "ECU ID: " << id << endl;
	}
};



int main() {

	//  ------  Exercise1: Pointer to Struct:  -------
	cout << "\nExercise1: Pointer to Struct" << endl;
	Sensor s1{10, 55.5f};
	
	Sensor* objectPtr = &s1;    // pointer to Sensor object

	// Use the pointer to print its members using 
	cout << "Sensor ID: " << objectPtr->id << endl;
	cout << "Sensor Reading: " << (*objectPtr).reading << endl;

	//  ------  Exercise2: Modify Struct Using Pointer:  -------
	cout << "\nExercise2: Modify Struct Using Pointer" << endl;

	cout << "Original Values: " << "{Sensor ID: " << (*objectPtr).id << ", Sensor Reading: " << objectPtr->reading << "}" << endl;

	// Modify sensor's value
	(*objectPtr).id = 20;
	objectPtr -> reading = 75.10f;

	// Print the modified value
	cout << "Modified Values: " << "{Sensor ID: " << (*objectPtr).id << ", Sensor Reading: " << objectPtr->reading << "}" << endl;

	//  ------  Exercise3: Dynamic Allocation of Struct:  -------
	cout << "\nExercise3: Dynamic Allocation of Struct" << endl;
	
	// Dynamically allocate a Sensor using new
	Sensor* newPtr = new Sensor;

	// Assign the values using the pointer
	(*newPtr).id = 101;
	newPtr->reading = 42.7f;

	// Print the values
	cout << "Dynamic Sensor ID: " << newPtr->id << endl;
	cout << "Dynamic Sensor Reading: " << newPtr->reading << endl;

	// Free the memory
	delete newPtr;

	cout << "Memory released." << endl;

	//  ------  Exercise4: Array of Structs + Pointer Traversal:  -------
	cout << "\nExercise4: Array of Structs + Pointer Traversal" << endl;

	// Static array of 3 sensors object
	Sensor sensors[3] = {
		{1, 10.1f},
		{2, 20.2f},
		{3, 30.3f} 
	};

	// A pointer to the first element of array
	Sensor* arrPtr = sensors;    // sensors decay to &sensors[0]

	// Using arithmetic (ptr + i) to print all sensors
	for (int i = 0; i < 3; ++i) {
		cout << "Sensor[" << i << "]: "
			<< "ID=" << (arrPtr + i)->id
			<< ", Reading=" << (arrPtr + i)->reading << endl;
	}

	//  ------  Exercise5: Function Accepting Pointer to Struct:  -------
	cout << "\nExercise5: Function Accepting Pointer to Struct" << endl;
	
	Sensor s4{ 5, 88.8f };
	Sensor* argPtr = &s4;
	
	printSensor(argPtr);

	//  ------  Exercise6: Function Returning a Pointer:  -------
	cout << "\nExercise6: Function Returning a Pointer" << endl;

	// Create an Array of Sensor
	Sensor arrSensor[5] = {
		{10, 55.52f},
		{23, 45.98f},
		{85, 37.31f},
		{12, 89.46f},
		{05, 38.45f}
	};

	// Function call
	Sensor* maxSensorReading = getMaxReading(arrSensor, 5);

	// Print result
	cout << "Max reading found: "
		<< "ID=" << maxSensorReading->id
		<< " Reading=" << maxSensorReading->reading
		<< endl;

	//  ------  Exercise7: Class + Pointer + Arrow Operator:  -------
	cout << "\nExercise7: Class + Pointer + Arrow Operator" << endl;

	ECU ecu1{ 500 };
	ECU* ecu1Ptr = &ecu1;

	// call ECU::printID() via pointer
	ecu1Ptr->printID();

	//  ------  Exercise8: Dynamic Object of Class + delete:  -------
	cout << "\nExercise8: Dynamic Object of Class + delete" << endl;

	ECU* ecuPtr = new ECU;
	ecuPtr->id = 777;
	cout << "Dynamically allocated ";
	ecuPtr->printID();
	cout << "Object Destroyed properly." << endl;

	delete ecuPtr;

	// End of Program
	return 0;
}

void printSensor(const Sensor* s) {

	cout << "Printing Sensor inside the function:" << endl;
	cout << "ID=" << (*s).id << " Reading=" << (*s).reading << endl;

}

Sensor* getMaxReading(Sensor* arrSensor, int size) {

	Sensor* maxvalue = arrSensor + 0;

	for (int i = 1; i < size; ++i) {
		if (maxvalue->reading < (arrSensor + i)->reading) {
			maxvalue = arrSensor + i;
		}
	}
	
	return maxvalue;
}