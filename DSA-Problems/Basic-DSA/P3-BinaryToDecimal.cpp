#include <iostream>
#include <string>

int main() {

	std::string str = "1011";

	int exponent = 1 << (str.length() - 1);   //  Left Bit shifting (powers of 2 only)
	int dec = 0;
	
	for (int i = 0; i < str.length(); ++i) {

		dec += (str[i] - '0') * exponent;

		exponent >>= 1;    // Right Bit shifting ( exponent = exponent >> 1)
	}

	std::cout << "dec: " << dec << std::endl;

	return 0;
}
