/*

	C++ if-else (Decision Making)

		Given an integer n. Your task is to check if the integer is greater than, less than or equal to 5.
		If the integer is greater than 5, then print "Greater than 5" (without quotes).
		If the integer is less than 5, then print "Less than 5".
		If the integer is equal to 5, then print "Equal to 5".
		Note:- Do not print the next line after the result.

	Examples :

		Input: n = 8
		Output:Greater than 5
		Explanation: 8 is greater than 5.

	Constraints:
		1 <= a, b <= 1018

	Expected Complexities
		Time Complexity: O(1)
		Auxiliary Space: O(1)

*/

#include <iostream>

using namespace std;

string compareFive(int n) {
	// code here
	if (n == 5) {
		return "Equal to 5";
	}
	else if (n > 5) {
		return "Greater than 5";
	}
	else {
		return "Less than 5";
	}

}

int main() {
	int n = 10;
	string result = compareFive(n);
}