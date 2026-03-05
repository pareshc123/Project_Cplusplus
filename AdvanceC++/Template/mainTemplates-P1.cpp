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


// Exercise 2
template<typename T>
bool areEqual(T a, T b) {
	return (a == b) ? true : false;
}

template<>
bool areEqual<const char*>(const char* a, const char* b) {
	return (strcmp(a, b) == 0) ? true : false;
}

int main() {

	cout << "================ Exercise1:Template Deduction Deep Dive ================" << endl;
	cout << "add(5, 10): " << add(5, 10) << "; Success !!" << endl;
	cout << "add(5.0, 2.5): " << add(5.0, 2.5) << ", Success !!" << endl;
	// cout << "add(5, 2.5): " << add(5, 2.5) << ", Failed -- different argument types !!" << endl;
	cout << "add('A', 'B'): " << add('A', 'B') << ", Success - but wrong results !!" << endl;
	cout << "add(5L, 10L): " << add(5L, 10L) << ", Success !!" << endl;
	// cout << "add(5, 10L): " << add(5, 10L) << ", Failed -- different argument types !!" << endl;

	cout << "\n================ Exercise2:Explicit Specialization ================" << endl;
	const char* a = "HELLO";
	const char* b = "HELLO";
	if (areEqual(a, b)) {
		cout << "Comparison of " << a << ", " << b << " is a Success !!" << endl;
	}
	else {
		cout << "Comparison of " << a << ", " << b << " is Failed !!" << endl;

	}



    return 0;
}