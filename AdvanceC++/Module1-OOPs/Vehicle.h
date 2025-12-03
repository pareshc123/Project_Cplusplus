#pragma once

#include <string>
#include "Engine.h"
#include <memory>

class Vehicle {
private:
    Engine eng;       // Composition

public:
    std::string brand;
    int year;

    // Constructors
    Vehicle();
    Vehicle(const std::string& brand, int yr);

    // Engine setup
    void setEngineInfo(const std::string& type, const std::string& fuel, int hp);

    // Engine getter
    const Engine& getEngine() const;

    // Utility
    void displayVehicleInfo() const;

    virtual ~Vehicle();

};
