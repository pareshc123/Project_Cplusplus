/*
    Difference Between i++ and ++i in C++ For Loops
    ------------------------------------------------
    In C++:

    1. i++ (post-increment)
       - Uses the current value first, then increments.
       - Example: int x = i++; // x gets old value, i increases
            int i = 5;
            int x = i++; // x = 5, i becomes 6

    2. ++i (pre-increment)
       - Increments first, then uses the new value.
       - Example: int x = ++i; // i increases first, x gets new value
            int i = 5;
            int x = ++i; // i becomes 6, x = 6

    In simple for loops with integer indices, both behave the same:
        for (int i = 0; i < n; i++) { ... }
        for (int i = 0; i < n; ++i) { ... }

    Key Note:
        - For primitive types like int:
            Both i++ and ++i behave the same in a for loop.
            The compiler optimizes away any difference, so performance is identical.

        - For objects or iterators (like vector iterators):
            i++ creates a temporary copy of the object/iterator because it must return the original value before incrementing.
            ++i increments the object/iterator directly without creating a temporary, 
            which avoids extra work and can be slightly more efficient.

    Additional Note:
      
        - Even though the output of i++ and ++i loops looks the same, 
            using ++i avoids creating unnecessary temporary objects internally for non-primitive types.
      
        - For primitive types (int), this efficiency difference is negligible.
*/

#include <iostream>
#include <vector>
using namespace std;

int main() {

    // --------------
    //  Example 1: Primitive type
    // --------------

	cout << "Example 1: Using post increment (i++) with primitive type (int):" << endl;

    for (auto i = 0; i < 5; i++) {
		cout << i << " ";
    }
    cout << endl;

	cout << "Example 1: Using pre increment (++i) with primitive type (int):" << endl;
    for (auto i = 0; i < 5; ++i) {
        cout << i << " ";
    }
	cout << endl << endl;

    // --------------
    //  Example 2: Using iterators (non-primitive type)
	// --------------
    
    vector<int> vec{ 1, 2, 3, 4, 5 };

	cout << "Example 2: Using post increment (it++) with vector iterator:" << endl;

    for (auto it = vec.begin(); it != vec.end(); it++) {
        cout << *it << " ";
	}
	cout << endl;

    cout << "Example 2: Using pre increment (++it) with vector iterator:" << endl;
    for (vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

	// End of Program
	return 0;
}
