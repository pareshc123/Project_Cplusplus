/*
    Regular For Loop in C++:
    -----------------------
    A for loop is used to execute a block of code repeatedly for a known number of iterations.

    Syntax:
        for (initialization; condition; update) {
            // code to execute
        }
    Example:
        for (int i = 0; i < 5; i++) {
            cout << i << endl;
        }

    Key Points:
        - 'initialization' runs once at the beginning.
        - 'condition' is checked before each iteration; loop stops if false.
        - 'update' runs after each iteration.
*/

/*
    Range-based For Loop in C++ (C++11 and above):
    ----------------------------------------------
    A range-based for loop is used to iterate directly over elements of a container or array.

    Syntax:
        for (datatype element : container) {
            // code to execute
        }
    Example:
        int arr[] = {1, 2, 3, 4, 5};
        for (int x : arr) {
            cout << x << endl;
        }

    Key Points:
        - 'element' represents each item in the container.
        - Simplifies iteration without using an index.
        - Works with arrays, vectors, and other STL containers.
*/

#include <iostream>
#include <vector>
using namespace std;

int main() {
    // Regular for loop using auto for index
    vector<int> numbers = { 10, 20, 30, 40, 50 };

    cout << "Regular for loop:" << endl;
    for (auto i = 0; i < numbers.size(); i++) {
        cout << numbers[i] << " ";
    }
    cout << endl << endl;

    // Range-based for loop using auto
    cout << "Range-based for loop:" << endl;
    for (auto num : numbers) {  // num automatically deduced as int
        cout << num << " ";
    }
    cout << endl << endl;

    // Range-based for loop using reference to modify elements
    cout << "Range-based for loop with reference (modifying elements):" << endl;
    for (auto& num : numbers) { // auto& allows modifying original vector
        num += 5;
        cout << num << " ";
    }
    cout << endl << endl;

    // Display final vector to show modification
    cout << "Final vector elements:" << endl;
    for (auto num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
