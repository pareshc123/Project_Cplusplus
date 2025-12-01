#include "Car.h"

Car::Car():numberOfDoors(0)
{
	cout << "\nCar [Parent Class] Default Constructor invoked" << endl;
}

Car::Car(string brand, int yr, int numDoors) :Vehicle(brand, yr), numberOfDoors(numDoors)
{
	cout << "\nCar [Child Class] Parametrized Constructor invoked" << endl;
}

Car::~Car()
{
	cout << "\nCar [Child Class] Destructor Invoked." << endl;
}
