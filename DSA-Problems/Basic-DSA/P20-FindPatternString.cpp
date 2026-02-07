/*
	Given a string s, and a pattern p. You need to find if p exists in s or not and return the starting index of p in s. If p does not exist in s then -1 will be returned.
	Here p and s both are case-sensitive.

	Examples:

		Input: s = "Hello", p = "llo"
		Output: 2
		Explanation: llo starts from the second index in Hello.
		Input: s = "World", p = "Doodle"
		Output: -1
		Explanation: Both are different.

	Expected Complexities
		Time Complexity: O(n)
		Auxiliary Space: O(1)

	NOTE:
		KMP (Knuth–Morris–Pratt) is a string pattern matching algorithm.
		It is used to find a pattern inside a text efficiently.

		Unlike the naive approach, KMP avoids rechecking characters by
		using information from the pattern itself (via the LPS array).

		Time Complexity: O(n + m)
		Used when fast substring search is required.

*/

#include <iostream>
#include <string>

using namespace std;

int findPatternSTL(string& s, string& p) {
	// code here

	int res = s.find(p);
	if (res != string::npos) {
		return res;
	}

	return -1;
}

int findPatternNaive(string& s, string& p) {
	// Manual (naive approach without KMP)

	// Chcek if string s is sgreater than p
	if (s.length() < p.length()) {

		return -1;
	}
	// now check the pattern
	for (int i = 0; i < s.length(); ++i) {
		int sTemp = i;
		int pTemp = 0;
		
		while (pTemp < p.length() and (s.length() - i > p.length())) {
			
			cout << "s[sTemp]: " << s[sTemp] << ", p[pTemp]: " << p[pTemp] << endl;
			if (s[sTemp] != p[pTemp]) {
				break;
			}
			else {
				++sTemp;
				++pTemp;

				if (pTemp == p.length()) {

					return i;
				}
			}
		}
	}
	return -1;

}

int findPatternKMP() {

	return -1;
}

int main(){

	string s1 = "Geekforgeeks";

	string s2 = "Geek";
	string s3 = "ksfo";
	string s4 = "Geeks";


	string s5 = "Hello";
	string s6 = "llo";

	int res3 = findPatternNaive(s1, s4);
	cout << res3 << endl;

	//int res1 = findPatternNaive(s1, s2);
	//int res1 = findPatternNaive(s1, s3);
	//int res1 = findPatternNaive(s1, s4);

	//int res2 = findPatternSTL(s1, s3);

}