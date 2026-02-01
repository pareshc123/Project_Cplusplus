#include <iostream>
#include <string>

void optimize_code(std::string& str) {

	std::cout << "*** Optimize code ***" << std::endl;

	int dec = 0;
	for (char c : str) {

		dec = dec * 2 + (c - '0');
	}

	std::cout << "dec: " << dec << std::endl;

}

int main() {

	std::string str = "1011";

	std::cout << "*** Method one ***" << std::endl;

	int exponent = 1 << (str.length() - 1);   //  Left Bit shifting (powers of 2 only)
	int dec = 0;
	
	for (int i = 0; i < str.length(); ++i) {

		dec += (str[i] - '0') * exponent;

		exponent >>= 1;    // Right Bit shifting ( exponent = exponent >> 1)
	}

	std::cout << "dec: " << dec << "\n" <<std::endl;

	optimize_code(str);

	return 0;
}
