/*
	This file introduces the basic of C++ for writing raw strings using user defined delimiter

	We write R so that the compiler doesnt treat \temp as \t = tab and emp differently and \num as new line + xt

	Custom delimiter: in the code below you will see MSG which is user defined delimiter introduced so that we can
	use "" within "" or else the compiler will end think string ended at second delimiter

	Note cusotm delimiter should not be more than 16 characters

*/

#include<iostream>
#include<string>

using namespace std;

void basicString() {

	// Raw string example failed:
	// std::string filename{"C:\temp\num.txt"};
	std::string filename{ R"(C:\temp\num.txt)" };

	cout << filename << endl;

	// Delimiter string example failed:
	// std::string filename1{ R"(C++ introduced filesystem API "(In C++17)")" };

	std::string filename1{ R"MSG(C++ introduced filesystem API "(In C++17)")MSG" };
	cout << filename1 << endl;

}


int main() {

	basicString();

	return 0;
}