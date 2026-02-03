/*
	Last Digit of a number

	Given an integer n. Write a program to find last digit of the number.

	Examples:

		Input: n = 10
		Output: 0
		Input: n = 9768
		Output: 8
	
	Expected Complexities
		Time Complexity: O(1)
		Auxiliary Space: O(1)

*/

#include <iostream>

using namespace std;

void utility(int n) {

	// just complete below statement
	int ans = abs(n % 10);

	// print the result
	cout << ans << endl;
}

int main() {

	int n = 535;  // or -435

	utility(n);

	return 0;
}