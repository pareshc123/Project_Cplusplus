#pragma once

#include <iostream>
#include <string>

using namespace std;

class Vehicle
{
public:
	std::string brand;
	int year;

	Vehicle();
	Vehicle(string brand, int yr);
	~Vehicle();
};
