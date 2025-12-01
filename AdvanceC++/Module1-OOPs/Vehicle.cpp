#include "Vehicle.h"

Vehicle::Vehicle() : brand(" "), year(0) {
	cout << "\nCar [Child Class] Default Constructor invoked" << endl;
}

Vehicle::Vehicle(string brand, int yr) : brand(brand), year(yr) {
	cout << "\nVehicle [Parent Class] Parametrized Constructor invoked" << endl;
}

Vehicle::~Vehicle() {
	cout << "\nVehicle [Parent Class] Destructor Invoked." << endl;
}
