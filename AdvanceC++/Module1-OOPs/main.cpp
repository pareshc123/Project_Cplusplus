#include "Vehicle.h"
#include "Car.h"

int main() {

	// Exericse 1: === Simple Inheritance ===
	cout << "\n=== Simple Inheritance ===" << endl;

	// default constructor
	Car c;
	c.brand = "BMW";
	c.year = 2023;
	c.numberOfDoors = 4;

	cout << "The details of your Car {brand: " << c.brand
		<< ", year: " << c.year << ",} with "
		<< c.numberOfDoors << " vertical opening doors." << endl;
}