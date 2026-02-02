/*
	
	Given a English alphabet c, Write a program to check whether a character is a vowel or not.

	Example 1:
		Input: c = 'a'
		Output: YES
		Explanation: 'a' is a vowel.

	Example 2:
		Input: c = 'Z'
		Output: NO
		Explanation: 'Z' is not a vowel.

	Your Task:
	You don't need to read input or print anything. 
	Your task is to complete the function isVowel() which takes a character c and returns 'YES' or 'NO'.

	Expected Time Complexity: O(1)
	Expected Auxiliary Space: O(1)

*/

#include <iostream>

using namespace std;

string isVowel(char c) {
	// code here
	char lc = (char)tolower(c);
	if (lc == 'a' || lc == 'e' || lc == 'i' || lc == 'o' || lc =='u') {
		return "YES";
	}
	else {
		return "NO";
	}
}

string isVowelOptimized(char c) {

	c = tolower(c);
	
	string vowels = "aeiou";
	return (vowels.find(c) != string::npos) ? "YES" : "NO";

	/*            =========== OR ===========
	unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
	return vowels.count(c) ? "YES" : "NO"
	*/
}

int main() {

	char c = 'Z';
	string result = isVowel(c);
	string result = isVowelOptimized(c);

	cout << result << endl;

}