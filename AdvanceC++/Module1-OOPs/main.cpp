#include "Vehicle.h"
#include "Car.h"

int main() {

	// Exericse 1: === Simple Inheritance ===
    std::cout << "\n=== Simple Inheritance Tests ===\n";

    // 1. Default constructor
    std::cout << "\n--- Default Constructor Test ---\n";
    Car c;
    c.brand = "BMW";
    c.year = 2023;
    c.numberOfDoors = 4;

    std::cout << "Car Details: { brand: " << c.brand
        << ", year: " << c.year
        << ", doors: " << c.numberOfDoors << " }\n";


    // 2. Parameterized constructor
    std::cout << "\n--- Parameterized Constructor Test ---\n";
    Car p("Porsche", 2024, 4);
    std::cout << "Car Details: { brand: " << p.brand
        << ", year: " << p.year
        << ", doors: " << p.numberOfDoors << " }\n";


    // 3. Pointer to base class (polymorphism test)
    std::cout << "\n--- Polymorphism Test (Base Pointer --> Derived Object) ---\n";
    Vehicle* vPtr = new Car("Audi", 2021, 2);
    std::cout << "Accessed through Vehicle*: " << vPtr->brand << ", " << vPtr->year << std::endl;
    delete vPtr;  // calls Car destructor first and then Vehicle destructor (because virtual!)

    // 4. Smart Pointer test (modern C++)
    std::cout << "\nSmart Pointers (unique_ptr) test\n" << std::endl;
    unique_ptr<Vehicle> conceptCar = make_unique<Car>("Mercedes", 1998, 2);
    std::cout << "Accessed through Unique_ptr<Vehicle>: "
        << conceptCar->brand << ", " << conceptCar->year << std::endl;
    // automatic car

    // 5. Array of Cars

    std::cout << "\n=== END OF EXERCISE 1 ===\n";

    // Exericse 2: === Composition ===
    std::cout << "\n=== Composition Test ===\n";

    std::cout << "\n=== END OF PROGRAM ===" << endl;


}