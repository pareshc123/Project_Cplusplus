#include <iostream>
#include <memory>

using namespace std;

struct Sensor {

	string name;
};

int main() {

	
	// Exercise1: uisng shared_ptr
	cout << "\nExercise1: uisng shared_ptr:" << endl;
	auto shrPtr1 = make_shared<Sensor>();
	shrPtr1->name = "CameraSensor";
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
 
	return 0;
}