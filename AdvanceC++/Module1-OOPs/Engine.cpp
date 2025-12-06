#include "Engine.h"
#include <iostream>

// Define Constructors and destructor
Engine::Engine() : engineType("Unknown"), fuelType(" Unknown"), horsepower(-1) {

	std::cout << "[Composition Class] Engine --- Default Constructor invoked" << std::endl;

}

Engine::Engine(const std::string& engineType, const std::string& fuelType, int hp){
	
	std::cout << "[Composition Class] Engine --- Parametrized Constructor invoked" << std::endl;

	this->engineType = engineType;
	this->fuelType = fuelType;
	horsepower = hp;

}

Engine::~Engine() {

	std::cout << "[Composition Class] Engine --- Destructor Invoked" << std::endl;

}


// Define Setters
void Engine::setEngineType(const std::string& engineType) {
	
	this->engineType = engineType;
}

void Engine::setFuelType(const std::string& fuel) {

	this->fuelType = fuel;
}

void Engine::setHorsePower(int hp) {

	this->horsepower = hp;
}


// Define getters
const std::string& Engine::getEngineType() const {

	return engineType;
}

const std::string& Engine::getFuelType() const {

	return fuelType;
}

int Engine::getHorsePower() const {

	return horsepower;
}


// Display Engine Information
void Engine::displayEngineInfo() const {

	std::cout << "Engine details:"
		<< " Engine Type: " << engineType
		<< ", Fuel Type: " << fuelType
		<< ", HorsePower: ";

	if (horsepower < 0) {
		std::cout << "N/A" << std::endl;
	}
	else {
		std::cout << horsepower << std::endl;
	}
}