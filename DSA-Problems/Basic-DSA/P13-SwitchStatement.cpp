/*
	
	Switch Statement

	Given a number, you have to use a switch statement to return "One" if the given number is equal to 1, 
	"Two" if the number is 2 and so on till 9 ("Nine") else return "Unknown"(without quotes).

	Examples:

		Input: number = 10
		Output: Unknown

		Input: number = 1
		Output: One

	Expected Complexities
		Time Complexity: O(1)
		Auxiliary Space: O(1)

*/
#include<iostream>
#include<string>

using namespace std;

string utility(int number) {

    // write your code here
    switch (number) {
    case 1:
        return "One";
    case 2: return "Two";

    case 3: return "Three";

    case 4: return "Four";

    case 5: return "Five";

    case 6: return "Six";

    case 7: return "Seven";

    case 8: return "Eight";

    case 9: return "Nine";

    default: return "Unknown";
    }
}

int main() {
    
    int number;
    cin >> number;
    string result = utility(number);
    return 0;
}