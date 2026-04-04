/*
	
	Description for templates:
	When Instantiation Happens
		1. Function call
			-> Max(3, 5);
		
		2. Taking function address
			-> auto ptr = &Max<int>;
		
		3. Explicit Instantiation
			-> template char Max(char, char);    
			(Note: In normal case, when you invoke/call the function only then compiler generates the function but here
				we Force compiler to generate it)
		
		4. Explicit Specialization
			-> template<>
			   char Max<char>(char a, char b);

	Note: Templates are included in Header files
			becasue Templates are generated at compile-time --> compiler needs full code.

*/

#include<iostream>
#include <cstring>

using  std::cout;
using  std::endl;


// Exercise 1: Primary template
template<typename T>
T add(T a, T b) {
	return a + b;
}

// Explicit instantiation
template int add<int>(int, int);
template double add<double>(double, double);
template char add<char>(char, char);

// Exercise 2: Explicit specialization
template<typename T>
bool areEqual(T a, T b) {
	return (a == b) ? true : false;   // ternary
}

template<>
bool areEqual<const char*>(const char* a, const char* b) {
	return strcmp(a, b) == 0;   // without ternary
}


// Exerice 3: Non type Template Argument
template <typename T, size_t  N>
void printArray(T(&arr)[N]) {
	cout << "Size of Array is: " << N << endl;
	for (int i = 0; i < N; ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
}


// Exercise 4: Compile Time Buffer
template<size_t N>
struct Buffer
{
	uint8_t data[N];

	void printSize() const
	{
		cout << "Buffer size = " << N << endl;
	}
};


int main() {

	cout << "================ Exercise1:Template Deduction Deep Dive ================" << endl;
	cout << "add(5, 10): " << add(5, 10) << "; Success !!" << endl;
	cout << "add(5.0, 2.5): " << add(5.0, 2.5) << ", Success !!" << endl;
	// cout << "add(5, 2.5): " << add(5, 2.5) << ", Failed -- different argument types !!" << endl;
	cout << "add('A', 'B'): " << add('A', 'B') << ", Success - but wrong results - use(int)add('A', 'B') for correct result !!" << endl;
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

	// I am not passing the size with c-sytle array and NTTA template deduces the Size
	printArray(arr1);
	printArray(arr2); 

	cout << "\n================ Exercise4: Compile time buffer ================" << endl;
	Buffer<8> canFrame{};
	Buffer<64> canFDFrame{};

	canFrame.printSize();
	canFDFrame.printSize();

	cout << "Size of canFrame object: " << sizeof(canFrame) << endl;
	cout << "Size of canFDFrame object: " << sizeof(canFDFrame) << endl;

	cout << "\n================ Exercise5: Function Pointer Instantiation ================" << endl;

	// Taking address of template function --> forces instantiation
	int(*maxIntPtr)(int, int) = add<int>;

	cout << "Function pointer call add<int>(2,3): " << maxIntPtr(2, 3) << endl;

    return 0;
}