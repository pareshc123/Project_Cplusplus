#include "Vehicle.h"

Vehicle::Vehicle()
    : brand("Unknown"), year(0)
{
    std::cout << "[Parent Class] Vehicle --- Default Constructor invoked" << std::endl;
}

Vehicle::Vehicle(const std::string& brand, int yr)
    : brand(brand), year(yr)
{
    std::cout << "[Parent Class] Vehicle --- Parameterized Constructor invoked" << std::endl;
}

Vehicle::~Vehicle()
{
    std::cout << "[Parent Class] Vehicle --- Destructor invoked" << std::endl;
}

// Setter Engine Configuration
void Vehicle::setEngineInfo(const std::string& engineType,const std::string& fuelType, int hp)
{
    eng.setEngineType(engineType);
    eng.setFuelType(fuelType);
    eng.setHorsePower(hp);
}

// Getter
const Engine& Vehicle::getEngine() const {
    return eng;
}

// Display vehicle info
void Vehicle::displayVehicleInfo() const {
    std::cout << "Vehicle Brand: " << brand
        << ", Year: " << year << "\n";

    eng.displayEngineInfo();
}