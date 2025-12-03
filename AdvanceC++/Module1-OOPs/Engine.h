#pragma once

#include <string>

class Engine {

	std::string engineType;
	std::string fuelType;
	int horsepower;

public:

	// constructors
	Engine();
	Engine(std::string engineType, std::string fuelType, int hp);
	
    // Getter and Setters


	void setEngineType(std::string& engine);
	std::string getEngineType()const;

	void setFuelType(std::string& fuel);
	std::string getFuelType()const;

	void setHorsePower(int& hp);
	const int getHorsePower()const;

	// Display Engine Information
	void displayEngineInfo() const;

	~Engine();
};