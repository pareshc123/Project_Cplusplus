#pragma once

#include <iostream>
#include <string>
#include "Engine.h"

using namespace std;

class Vehicle
{
	Engine eng;

public:
	std::string brand;
	int year;

	Vehicle();
	Vehicle(const std::string& brand, int yr);
	virtual ~Vehicle();
};
