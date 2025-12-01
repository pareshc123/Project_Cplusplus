#include "Vehicle.h"

Vehicle::Vehicle()
    : brand(""), year(0)
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
