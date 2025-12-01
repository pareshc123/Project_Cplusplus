#pragma once

#include "Vehicle.h"

class Car : public Vehicle
{
public:
    int numberOfDoors;

    Car();
    Car(std::string brand, int yr, int numDoors);
    ~Car();
};
