/*
	Given an array arr of integers and an index key(0-based index). Your task is to return the element present at the index key in the array.

	Examples:

		Input: key = 2 , arr = [10, 20, 30, 40, 50]
		Output: 30
		Explanation: The value of arr[2] is 30 .

		Expected Time Complexity: O(1)
		Expected Auxiliary Space: O(1)

		Constraints:
		0 <= key <= arr.size - 1
		1 <= arr.size <= 106
		1 <= arr[i] <= 109
*/

#include <iostream>
#include <vector>

using namespace std;


int findElementAtIndex(int key, vector<int>& arr) {
    // code here

    if (key >= 0 && key < arr.size()) {
        return arr[key];
    }

    return -1;  // or any sentinel value expected by the problem
}

int findElementAtIndexSimple(int key, vector<int>& arr) {

	return arr[key];
}

int main() {
	
	int key = 2;
	vector<int> arr = { 10, 20, 30, 40, 50 };

	// optimize without checking conditions
	int result = findElementAtIndexSimple(key, arr);

	// checking conditions and optimized
	int result = findElementAtIndex(key, arr);

}