/*
	GCD (Greatest common Divisor) or HCF (Highest common factor)

	Given two numbers A and B. The task is to find the GCD of  A and B.
	The GCD of two numbers is the largest number that can divide both A and B perfectly.

	Examples:

		Input: A = 6, B = 9
		Output: 3
		Explanation: After 3 there is no number that can divide both 6 and 9 perfectly.
		Input: A = 10, B = 15
		Output: 5
		Explanation: 5 is the greatest common divisor of 10 and 15.
	
	Constraints:
	1  <=  A, B  <=  100

	Expected Complexities
		Time Complexity: O(n)
		Auxiliary Space: O(1)

*/

int gcd(int a, int b) {
    // code here to calculate and return gcd of a and b

    if (a == 0) {
        return b;
    }

    if (b == 0) {
        return a;
    }

    if (a > b) {
        return gcd(a - b, b);
    }
    else {
        return gcd(a, b - a);
    }

}

int main() {

	int res = gcd(18, 24);
}