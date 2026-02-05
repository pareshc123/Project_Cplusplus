/*
	Given a string s, you need to reverse it.

	Examples:

		Input: s = "Hello"
		Output: "olleH"
		Explanation: Reverse of Hello is olleH
		Input: s = "World"
		Output: "dlroW"
		Explanation: Reverse of World is dlroW

	Expected Complexities
		Time Complexity: O(n)
		Auxiliary Space: O(n)
*/

#include<iostream>
#include<string>

using namespace std;

string reverseString(string& s) {
	// code here
	string n_string;

	for (int i = s.length() - 1; i >= 0; --i) {
		n_string += s[i];
	}

	return n_string;
}


int main() {

	string s;
	getline(cin, s);
	string result = reverseString(s);
	cout << result << endl;
	return 0;
}