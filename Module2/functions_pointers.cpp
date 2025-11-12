/*
    Function Pointers in C++
    ------------------------
    A function pointer is a pointer that stores the address of a function.
    It allows indirect calling of functions, passing functions as arguments,
    and storing multiple functions in arrays.

    Syntax:
        return_type (*pointer_name)(parameter_types);

    Example:
		int Add(int a, int b); // the function prototype

		int (*funcPtr)(int, int) = Add;  // function pointer declaration and initialization
                ----   or   ----
        int (*funcPtr)(int, int)
        funcPtr = Add;

		int result = funcPtr(5, 10);  // calling the function via pointer

    Notes:
        - '&' before function name is optional.
        - Call via pointer: funcPtr(args);
    
    Why use Function Pointers?

        - Call different functions dynamically without if/switch
        - Pass functions as arguments to other functions
        - Store multiple functions in an array

*/

#include <iostream>
#include <string>

using namespace std;

// Define Funtion prototypes
int Add(int a, int b);  // Simple function pointer 
int Subtract(int a, int b);
int Multiply(int a, int b);
void EndProgram();

int main() {

    // 1. Declare the simple function pointer
    int (*addfuncPtr)(int, int);

	// 2. Assign the address of Add function to the pointer
	addfuncPtr = Add;  // or use &Add

	// 3. Call the function via pointer
	int sum = addfuncPtr(10, 20);  // or (*addfuncPtr)(10, 20)

	cout << "Sum via function pointer: " << sum << endl;

	// 4. declare and initialize Array of function pointer
	int (*operations[3]) (int, int) = { Add, Subtract, Multiply };

    int x{10}, y{5};

    string names[3] = { "Sum", "Subtract", "Multiply" };

    cout << "\nCall function pointers via Range loop: " << endl;
	// 5. Use range-based for loop to iterate through function pointers
	int counter = 0;
    for (auto oper : operations) {
		cout << names[counter] << ": " << oper(x, y) << endl;
		counter++;
    }

    /*
	Instead of auto, we can explicitly declare the type in the range-based for loop. However, it is not common practice.
        for (int (*oper)(int,int) : operations) {
        cout << names[counter] << ": " << oper(x, y) << endl;
        counter++;
        }
    */
    
    cout << "\nCall function pointers via simple FOR loop: " << endl;
	// 6. Use For loop to iterate through function pointers
    for (int i = 0; i < 3; i++) {
		cout <<  names[i] << ": " << operations[i](x, y) << endl;
    }

	//7. Pointer to void function
	atexit(EndProgram);  // register EndProgram to be called at exit

	// End of Program
    return 0;
}

// Function Definitions
int Add(int a, int b) {

	return a + b;
}

int Subtract(int a, int b) {
    return a - b;
}

int Multiply(int a, int b) {
    return a * b;
}

void EndProgram() {
    cout << "\nEnd of Program." << endl;
}