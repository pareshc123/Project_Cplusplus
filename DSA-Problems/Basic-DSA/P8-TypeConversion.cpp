/*

	TypeCast And Double It:

	Difficulty: BasicAccuracy: 62.79%Submissions: 76K+Points: 1
	Given an input num as a string. You need to typecast into an integer and double it. 

	Examples:

	Input: num = "5"
	Output: 10
	Explanation: Typecast "5" to int and then double it 5 * 2 = 10

	Constraints:
		0 <= num <= 105

	Expected Complexities
		Time Complexity: O(1)
		Auxiliary Space: O(1)

	Note: Look for the trap at the bottom

*/

#include <iostream>
#include <string>
using namespace std;

int main() {

	string num;
	getline(cin, num);
	// TypeCast to int double it and print

	cout << stoi(num) * 2;

	return 0;
}

/*
	NOTE (Common Trap – Important for Interviews):

	The input is given as a std::string, not as an integer.

	In C++, a string like:
		"123"
	is NOT treated as the number 123.
	Internally, it is stored as a sequence of characters:
		'1', '2', '3'

	Because of this:
		static_cast<int>(num)   X
		(int)num                X
	do NOT work for converting a string to an integer.
	C++ has no built-in way to automatically convert a std::string into a number using casting.

	Why?
	Casting only changes the type of a value, not its meaning.
	A std::string is a class object, not a numeric type.

	Correct way:
	To convert a numeric string to an integer, we must PARSE it using:
		stoi(num)   // string to integer

	Other related functions:
		stol()   --> string to long
		stoll()  --> string to long long
		stod()   --> string to double

	Common Interview Pitfalls:
	1) Trying to cast std::string to int using (int) or static_cast<int>
	2) Confusing character conversion with string conversion
	3) Assuming input "5" behaves the same as integer 5
	4) Forgetting that '5' (char) has ASCII value 53, not numeric 5

	Key Rule:
	Casting is not equal to Parsing
	Strings must be parsed, not cast.

	IMPORTANT:
	if char c = '5';
	int x = c - '0';  // Correct --> 5

	or else according to ASCII '5' will be converted to 53 if you do int(c) or static_cast<int> c

*/

