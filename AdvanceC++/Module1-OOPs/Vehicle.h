#pragma once

#include <string>
#include "Engine.h"
#include <memory>
#include <typeinfo>

class Vehicle {
private:
    Engine eng;       // Composition

public:
    std::string brand;
    int year;

    // Constructors
    Vehicle();
    Vehicle(const std::string& brand, int yr);
    Vehicle(const std::string& brand, int yr, const Engine& e);

    // Engine setup
    void setEngineInfo(const std::string& type, const std::string& fuel, int hp);

    // Engine getter
    const Engine& getEngine() const;

    // Utility
    virtual void displayVehicleInfo() const;
    virtual std::string getType() const = 0;        // pure virtual function (Make Vehicle an abstract class)

    virtual ~Vehicle();

};
