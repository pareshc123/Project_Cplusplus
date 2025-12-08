#include <memory>
#include <vector>

#include "Car.h"
#include "Motorcycle.h"


int main() {

	std::cout << "\n=== START OF EXERCISE 3 ===\n";

	std::cout << "\n=== Create Engine objects ===" << std::endl;
	Engine eCar("V8", "Diesel", 450);
	Engine eMoto("Parallel Twin", "Petrol", 70);

	std::vector<Vehicle*> vehicles;

	std::cout << "\n=== Create Vehicle Child objects ===" << std::endl;
	vehicles.push_back(new Car("BMW", 2020, 4, eCar));
	vehicles.push_back(new Motorcycle("Yamaha", 2022, eMoto, Quad));

	std::cout << "\n=== Display Vehicle information ===" << std::endl;
	for (auto* v : vehicles) {
		std::cout << "Type: " << v->getType();
		v->displayVehicleInfo();
	}

	std::cout << std::endl;

	for (auto* v : vehicles) {
		delete v;
	}

	return 0;
}