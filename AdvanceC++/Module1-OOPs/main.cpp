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

    // 4. Smart Pointer test (modern C++)

    // 5. Array of Cars

    std::cout << "\n=== END OF EXERCISE 1 ===\n";

    // Exericse 2: === Composition ===
    std::cout << "\n=== Composition Test ===\n";

    std::cout << "\n=== END OF PROGRAM ===" << endl;


}