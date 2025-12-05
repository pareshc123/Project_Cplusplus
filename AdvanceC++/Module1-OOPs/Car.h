#pragma once

#include "Vehicle.h"

class Car : public Vehicle
{
public:
    int numberOfDoors;

    Car();                                                 // Default constructor
    Car(const std::string& brand, int yr, int numDoors);   // Parameterized constructor

    void displayVehicleInfo() const override;

    ~Car() override;                                                // Destructor
};
