#pragma once
#include "Vehicle.h"

// Enum representing motorcycle types
enum BikeType {
    Sport,
    Cruiser,
    Touring,
    Dirt,
    Quad,
    Scooter,
    NotDefined
};

class Motorcycle :
    public Vehicle
{

protected:
    BikeType bikeType;

public:

    Motorcycle();
    Motorcycle(const std::string& brand, int yr, BikeType type);
    Motorcycle(const std::string& brand, int yr, const Engine& e, BikeType type);

    // Display motorcycle-specific info
    void displayVehicleInfo() const override;

    // Override abstract function
    std::string getType() const override;

    ~Motorcycle();

};

