#include "Car.h"

Car::Car()
    : Vehicle(), numberOfDoors(0)
{
    std::cout << "[Child Class] Car --- Default Constructor invoked" << std::endl;
}

Car::Car(const std::string& brand, int yr, int numDoors)
    : Vehicle(brand, yr), numberOfDoors(numDoors)
{
    std::cout << "[Child Class] Car --- Parameterized Constructor invoked" << std::endl;
}

Car::Car(const std::string& brand, int yr, int numDoors, const Engine& e)
    : Vehicle(brand, yr, e), numberOfDoors(numDoors)
{
    std::cout << "[Child Class] Car --- Parameterized Constructor invoked" << std::endl;
}

void Car::displayVehicleInfo() const
{
    std::cout << "\n    Brand: " << brand
        << ", Year: " << year 
        << ", Num of Doors: " << numberOfDoors <<  "\n";

    getEngine().displayEngineInfo();   
}

std::string Car::getType() const {

    return "Class Car";
}


Car::~Car()
{
    std::cout << "[Child Class] Car --- Destructor invoked" << std::endl;
}
