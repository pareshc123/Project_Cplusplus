#include "Motorcycle.h"
#include <iostream>

// Local helper functions (not visible outside Motorcycle.cpp)
namespace {
    std::string bikeTypeToString(BikeType type)
    {
        switch (type) {
        case BikeType::Sport: return "Sport";
        case BikeType::Cruiser: return "Cruiser";
        case BikeType::Touring: return "Touring";
        case BikeType::Dirt: return "Dirt";
        case BikeType::Quad: return "Quad";
        case BikeType::Scooter: return "Scooter";
        default: return "Unknown";
        }
    }

    int numOfWheels(BikeType type)
    {
        return (type == BikeType::Quad ? 4 : 2);
    }
}

Motorcycle::Motorcycle()
    : bikeType(BikeType::NotDefined)
{
    std::cout << "[Child Class] MotorCycle --- Default Constructor invoked\n";
}

Motorcycle::Motorcycle(const std::string& brand, int yr, BikeType type)
    : Vehicle(brand, yr), bikeType(type)
{
    std::cout << "[Child Class] MotorCycle --- Parameterized Constructor invoked\n";
}

Motorcycle::Motorcycle(const std::string& brand, int yr, const Engine& e, BikeType type)
    : Vehicle(brand, yr, e), bikeType(type)
{
    std::cout << "[Child Class] MotorCycle --- Parameterized Constructor invoked\n";
}

void Motorcycle::displayVehicleInfo() const
{
    std::cout << "\n    Brand: " << brand
        << ", Year: " << year
        << ", Type: " << bikeTypeToString(bikeType)
        << "Number of Wheels: " << numOfWheels(bikeType) << "\n";

    getEngine().displayEngineInfo();
}

std::string Motorcycle::getType() const
{
    return "Class Motorcycle";
}

Motorcycle::~Motorcycle()
{
    std::cout << "[Child Class] MotorCycle --- Destructor invoked\n";
}
