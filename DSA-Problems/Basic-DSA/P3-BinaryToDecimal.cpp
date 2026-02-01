/*

	Given a string b representing a Binary Number, The problem is to find its decimal equivalent.

	Examples:

	Input : b = 111
		Output : 7
		Explanation : The decimal equivalent of the binary number 111 is 22 + 21 + 20 = 7.
	
	Input : b = 1010
		Output : 10
		Explanation : The decimal equivalent of the binary number 1010 is 23 + 21 = 10.
	
	Input: b = 100001
		Output: 33
		Explanation : The decimal equivalent of the binary number 100001 is 25 + 20 = 33.
	
	Constraints:
		1 <= number of bits in binary number  <= 16

	Expected Complexities
		Time Complexity: O(log n)  
		Auxiliary Space: O(1)

*/

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
