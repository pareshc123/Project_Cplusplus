/*

	Given two numbers a and b. Your task is to return the sum of a and b.

	Examples:

		Input: a = 1, b = 2
		Output: 3
		Explanation: Addition of 1 and 2 is 3.
	
		Input: a = 10, b = 20
		Output: 30
		Explanation: Addition os 10 and 20 is 30.
	
	Constraints:
		1 <= a, b <= 1018

	Expected Complexities
		Time Complexity: O(1)
		Auxiliary Space: O(1)

*/

#include <iostream>

using namespace std;

int addition(int a, int b) {
	return a + b;
}

int main() {
	int a{ 10 }, b{ 5 };
	int result = addition(a, b);
}