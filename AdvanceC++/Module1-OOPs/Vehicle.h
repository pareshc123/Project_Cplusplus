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
	Vehicle(const std::string& brand, int yr);
	virtual ~Vehicle();
};
