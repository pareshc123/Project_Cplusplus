/*

    Given three positive integers a, b and c. Your task is to perform some bitwise operations on them as given below:
        1. d = a ^ a
        2. e = c ^ b
        3. f = a & b
        4. g = c | (a ^ a)
        5. e = ~ e
        Note: ^ is for xor.
        Then print d e f g space seperately. Move the cursor to the next line after printing.

        Examples:

            Input: a = 1, b = 2, c = 3
            Output: 0 -2 0 3
            Explanation: We print d e f g after performing the given operations.

            Input: a = 4 , b = 5 , c = 6
            Output: 0 -4 4 6
            Explanation: We print d e f g after performing the given operations.

    Expected Complexities
        Time Complexity: O(1)
        Auxiliary Space: O(1)

*/

#include <iostream>

int main() {

	int a, b, c;
	std::cin >> a, b, c;

	// Bitwise Operations
    int d, e, f, g;
    // perform bitwise operations here
    d = a ^ a;
    e = c ^ b;
    f = a & b;
    g = c | (a ^ a);
    e = ~e;

    std::cout << d << " " << e << " " << f << " " << g;

	return 0;
}