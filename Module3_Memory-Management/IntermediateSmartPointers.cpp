/*
	SMART POINTERS — Intermediate Exercises
	---------------------------------------

*/

#include <iostream>
#include <memory>

using namespace std;

struct Sensor {

	string name="";

	Sensor() {
		cout << "Default_Sensor [" << name << "] Created." << endl;
	}

	Sensor(string n) :name(n) {
		cout << "Paramterized_Sensor [" << name << "] Created." << endl;
	}
	~Sensor() {
		cout << "Sensor [" << name << "] destroyed." << endl;
	}
};

struct ECUDeleter {

	void operator()(int* ptr) const {
		cout << "ECU Memory freed" << endl;
		delete ptr;
	}
};

int main() {

	
	// Exercise1: uisng shared_ptr
	cout << "\nExercise1: uisng shared_ptr:" << endl;
	auto shrPtr1 = make_shared<Sensor>("CameraSensor");
	shared_ptr<Sensor> shrPtr2 = shrPtr1;
	shared_ptr<Sensor> shrPtr3 = shrPtr1;
	
	cout << "Reference Count: " << shrPtr3.use_count() << endl;

	// Exercise2: weak_ptr + expiration check
	cout << "\nExercise2: weak_ptr + expiration check:" << endl;
	auto batteryPtr = make_shared<int>(90);
	weak_ptr<int> weakBatteryPtr = batteryPtr;

	cout << "Output of ptr.expired(): " << weakBatteryPtr.expired() << endl;
	cout << "Resetting the batter Ptr object ..." << endl;
	batteryPtr.reset();
	cout << "Output of ptr.expired(): " << weakBatteryPtr.expired() << endl;

	// Exercise3: unique_ptr to a dynamic array
	cout << "\nExercise3: unique_ptr to a dynamic array:" << endl;
	auto arrPtr = make_unique<int[]>(5);
	for (int i = 0; i < 5; ++i) {
		*(arrPtr.get() + i) = i*10;
	}
	cout << "Dynamic Array: ";
	for (int i = 0; i < 5; ++i) {
		cout << *(arrPtr.get() + i) << " ";
	}
	cout << endl;
	
	// Exercise4: Custom deleter
	cout << "\nExercise4: Custom deleter:" << endl;
	unique_ptr<int, ECUDeleter> ecuptr(new int(55));    // unique_ptr < TYPE , DELETER >
	cout << "ECU stored value = " << *ecuptr << "\n";
	
	cout << "\n--- END OF INTERMEDIATE EXERCISES ---\n\n";

	return 0;
}