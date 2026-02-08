/*
	Given a string s, you need to slice it so that the output is a substring that contains all the characters except the first and last.
	Note: The length of the s will be greater than 2. 

	Examples:

	Input: s = "Hello"
	Output: ell
	Explanation: The first and last character are ignored.

	Input: s = "World"
	Output: orl
	Explanation: The first and last characters are ignored.

	Hint: You can use s.substring(start, end)

	Expected Complexities
	Time Complexity: O(n)
	Auxiliary Space: O(n)

*/

#include<iostream>
#include<string>

std::string sliceStringNaive(std::string& s) {
	// code here
	std::string sub_s = "";

	for (int i = 0; i < s.length(); ++i) {

		if (i != 0) {
			if (i < s.length() - 1) {
				sub_s = sub_s + s[i];
			}
		}
	}

	return sub_s;
}

std::string sliceStringoptimize(std::string& s) {

	std::string sub_s = s.substr(1, s.length() - 2);
	return sub_s;
}

int main() {

	std::string str = "Hello";
	std::string result1 = sliceStringNaive(str);
	std::string result2 = sliceStringoptimize(str);

	std::cout << result1 << std::endl;
	std::cout << result2 << std::endl;
}