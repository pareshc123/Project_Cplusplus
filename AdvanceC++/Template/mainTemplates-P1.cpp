/*
	
	Description for templates:

*/

#include<iostream>

using  std::cout;
using  std::endl;


// Exercise 1: Primary template
template<typename T>
T add(T a, T b) {
	return a + b;
}


// Exercise 2: Explicit specialization
template<typename T>
bool areEqual(T a, T b) {
	return (a == b) ? true : false;
}

template<>
bool areEqual<const char*>(const char* a, const char* b) {
	return (strcmp(a, b) == 0) ? true : false;
}


// Exerice 3: Non type Template Argument
template <typename T, int N>
void printArray(T(&arr)[N]) {
	cout << "Size of Array is: " << N << endl;
	for (int i = 0; i < N; ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
}


int main() {

	cout << "================ Exercise1:Template Deduction Deep Dive ================" << endl;
	cout << "add(5, 10): " << add(5, 10) << "; Success !!" << endl;
	cout << "add(5.0, 2.5): " << add(5.0, 2.5) << ", Success !!" << endl;
	// cout << "add(5, 2.5): " << add(5, 2.5) << ", Failed -- different argument types !!" << endl;
	cout << "add('A', 'B'): " << add('A', 'B') << ", Success - but wrong results !!" << endl;
	cout << "add(5L, 10L): " << add(5L, 10L) << ", Success !!" << endl;
	// cout << "add(5, 10L): " << add(5, 10L) << ", Failed -- different argument types !!" << endl;

	cout << "\n================ Exercise2: Explicit Specialization ================" << endl;
	const char* a = "HELLO";
	const char* b = "HELLO";
	if (areEqual(a, b)) {
		cout << "Comparison of " << a << ", " << b << " is a Success !!" << endl;
	}
	else {
		cout << "Comparison of " << a << ", " << b << " is Failed !!" << endl;

	}

	cout << "\n================ Exercise3: Array Size Deduction ================" << endl;
	int arr1[4] = { 1,2,3,4 };
	double arr2[3] = { 1.1,2.2,3.3 };

	printArray(arr1);
	printArray(arr2);

	cout << "\n================ Exercise4: Compile time buffer ================" << endl;

    return 0;
}