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

struct Sensor {
	int id;
	float reading;
};

using namespace std;

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


	// End of Program
	return 0;
}