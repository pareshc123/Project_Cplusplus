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

    cout << "\n=== END OF PROGRAM ===" << endl;

}