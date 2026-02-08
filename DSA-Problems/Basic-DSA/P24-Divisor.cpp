/*
	Given an integer N. Write a program to print all the divisors of N in a single line.

	Examples:

	Input: N = 12
	Output: 1 2 3 4 6 12
	Explanation: 12 is divisible by 1 2 3 4 6 12.

	Input: N = 10
	Output: 1 2 5 10
	Explanation: 10 is divisible by 1 2 5 10.

	Constraints:
	1 <= n <= 105

	Expected Complexities
	Time Complexity: O(n)
	Auxiliary Space: O(1)


*/

#include<iostream>

using namespace std;

void divisor(int n) {

	// Write your code here
	for (int i = 1; i <= n; ++i) {

		if (n % i == 0) {
			cout << i << " ";
		}
	}
}

int main() {

	divisor(12);

	return 0;
}
