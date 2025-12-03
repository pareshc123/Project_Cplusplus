#pragma once

#include <string>
#include <iostream>

class Engine {
private:
    std::string engineType;
    std::string fuelType;
    int horsepower;

public:
    // Constructors
    Engine();
    Engine(const std::string& type, const std::string& fuel, int hp);

    // Setters
    void setEngineType(const std::string& type);
    void setFuelType(const std::string& fuel);
    void setHorsePower(int hp);

    // Getters (const ensures the object is not modified)
    const std::string& getEngineType() const;
    const std::string& getFuelType() const;
    int getHorsePower() const;

    // Utility
    void displayEngineInfo() const;

    // Destructor
    ~Engine();
};
