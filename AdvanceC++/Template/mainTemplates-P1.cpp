/*
	
	Description for templates:

*/

#include<iostream>

using  std::cout;
using  std::endl;


// Exercise 1
template<typename T>
T add(T a, T b) {
	return a + b;
}


int main() {

	cout << "================ Exercise1:Template Deduction Deep Dive ================" << endl;
	cout << "add(5, 10): " << add(5, 10) << "; Success !!" << endl;
	cout << "add(5.0, 2.5): " << add(5.0, 2.5) << ", Success !!" << endl;
	// cout << "add(5, 2.5): " << add(5, 2.5) << ", Failed -- different argument types !!" << endl;
	cout << "add('A', 'B'): " << add('A', 'B') << ", Success - but wrong results !!" << endl;
	cout << "add(5L, 10L): " << add(5L, 10L) << ", Success !!" << endl;
	// cout << "add(5, 10L): " << add(5, 10L) << ", Failed -- different argument types !!" << endl;

    return 0;
}