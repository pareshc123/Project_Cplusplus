/*
    Function Overloading in C++
    ---------------------------
    Function overloading allows multiple functions to share the same name
    but differ in their parameter list (number, types, or const qualifiers).

    - The compiler chooses which version to call based on argument types.
    - Overloaded functions must differ by argument list, not by return type.
    - Const qualifiers on references or pointers also participate in overload.
    - This decision happens at compile time (Static Polymorphism).

    Example:
        int Add(int a, int b);
        double Add(double a, double b);

    Function calls:
        Add(3, 4);       // calls Add(int, int)
        Add(2.5, 4.1);   // calls Add(double, double)

    Internally, the compiler generates unique names for overloaded functions
    using a process called Name Mangling.

    To make a C++ function callable from C (no name mangling):
        extern "C" void FunctionName();

    Note:
        extern "C" can be applied only to one version of an overloaded function.
        If applied in a header, it must also be used in the definition.
*/


#include <iostream>

using namespace std;

// Function prototypes
int Multiply(int a, int b);
double Multiply(double a, double b);
double Multiply(int a, double b);
void Display(int& a);
void Display(const int& a);
extern "C" void ShowMessage(); // Example of extern "C" usage

int main() {

	// variable declaration
    double num1;
    double num2;

    for (int i = 0; i < 1; i++) {
		cout << "Enter two numbers: ";
        cin >> num1 >> num2;
        cout << "Here is the output of your numbers: " << Multiply(num1, num2) << endl;
    }

    // Demonstrating function overloading with const reference
    int x = 10;
    const int y = 20;

    Display(x); // calls non-const version
    Display(y); // calls const version

	ShowMessage(); // Call the extern "C" function

	// End of the program
	return 0;
}

int Multiply(int a, int b) {
    return a * b;
}

double Multiply(double a, double b) {
    return a * b;
}

double Multiply(int a, double b) {
    return a * b;
}

void Display(int& a) {
	cout << "Non-const Display: " << a << endl;
}

void Display(const int& a) {
	cout << "Const Display: " << a << endl;
}

// extern "C" example (no name mangling)
extern "C" void ShowMessage() {
    cout << "This function has no name mangling and can be called from C." << endl;
}