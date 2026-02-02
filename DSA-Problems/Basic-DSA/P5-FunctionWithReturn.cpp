/*
	Here one integer n is given. You need to write the complete function returnValueFunction that takes n as a parameter and uses the return keyword to return double the value of n.

	Examples:

		Input: n = 2
		Output: 4
		Explanation: 2 * 2 = 4
	
	Constraints:
		1 <= n <= 5

	Expected Complexities
		Time Complexity: O(1)
		Auxiliary Space: O(1)
*/

#include <iostream>

using namespace std;

int returnValueFunction(int& x) {
	return 2 * x;
}

int main() {

	int x = 5;
	int result = returnValueFunction(x);
}