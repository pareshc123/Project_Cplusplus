#include "Engine.h"
#include <iostream>

// Define Constructors and destructor
Engine::Engine() : engineType(" "), fuelType(" "), horsepower(0) {

	std::cout << "[Composition Class] Engine --- Default Constructor invoked" << std::endl;

}

Engine::Engine(std::string engineType, std::string fuelType, int hp){
	
	std::cout << "[Composition Class] Engine --- Parametrized Constructor invoked" << std::endl;

	this->engineType = engineType;
	this->fuelType = fuelType;
	horsepower = hp;

}

Engine::~Engine() {

	std::cout << "[Composition Class] Engine --- Destructor Invoked" << std::endl;

}


// Define getters and Setters
void Engine::setEngineType(std::string& engine) {
	
	this->engineType = engine;
}

std::string Engine::getEngineType() const {

	return engineType;
}

void Engine::setFuelType(std::string& fuel) {

	this->fuelType = fuel;
}

std::string Engine::getFuelType() const {

	return fuelType;
}

void Engine::setHorsePower(int& hp) {

	this->horsepower = hp;
}

const int Engine::getHorsePower() const {

	return horsepower;
}


// Display Engine Information
void Engine::displayEngineInfo() const {

	std::cout << "Engine details: " << std::endl;
	std::cout << "   Engine Type: " << engineType << std::endl;
	std::cout << "   Fuel Type: " << fuelType << std::endl;
	std::cout << "   HorsePower: " << horsepower << std::endl;
}