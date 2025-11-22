/*

	PART 3 — Pointers + Functions

		Function pointers (how to declare them)
		Calling functions via pointers
		Passing function pointers as parameters
		Returning function pointers from functions
		Function pointer tables (used in ECUs for service dispatch)
	
	1. What is a Function Pointer? ==> A function pointer is a variable that stores the address of a function.
	
		// Normal function
		int add(int a, int b) {
			return a + b;
		}
	
		// Function pointer
		int (*funcPtr)(int, int);

		Meaning:

			funcPtr is a pointer
			to a function
			that takes (int, int)
			and returns int

		Now assign:
		funcPtr = &add;   // or simply = add;

		call it:
		int result = funcPtr(10, 20);

	2. Passing Function Pointers to Other Functions. why ?? ==> To allow a function to run a callback.
		Note: The function (in below example: execute()) that would receive a function pointer(*operation with two int arguments) 
			  as a argument can call back the function (execute(add)) that this pointer will point to.
		
		void execute(int (*operation)(int, int)) {   // function pointer as an argument
			int result = operation(10, 5);          // call-back function, since pointer (*operation) is pointing toward add()
		}

		int main(){
			
			int (*Ptr)(int, int) = add;
			execute(add);  // call it;

				OR

			execute(add);  because name of the function itself return the address.
		}
		This is how:
			hardware callbacks
			interrupt handlers
			sensor processing
			state machines

		are written.

	3. Returning Function Pointers
		
		int add(int a, int b) { return a + b; }
		int sub(int a, int b) { return a - b; }

		int (*getOperation(char op))(int, int)
		{
			if (op == '+') return add;
			else return sub;
		}

		// call
		auto func = getOperation('+');
		int result = func(10, 20);

	4. Array of Function Pointers

		int add(int a, int b);
		int sub(int a, int b);
		int mul(int a, int b);

		int (*operations[3])(int, int) = { add, sub, mul };

		// call
		int result = operations[2](5, 3);  // calls mul(5,3)

*/

#include <iostream>

using namespace std;

// Function prototype (declaration)
int add(int a, int b);
int sub(int a, int b);
int mul(int a, int b);

int main() {

	//  ------  Exercise1: Basic Function pointer:  -------
	cout << "\nExercise1: Basic Function Pointer:" << endl;
	int (*basicPtr)(int, int);

	cout << "\nAssigning the Addition function to basicPtr: " << endl;
	basicPtr = add;
	cout << "  Calling the function via Pointer : " << endl;
	cout << "  The output of Addition(10, 5) is: " << basicPtr(10, 5) << endl;

	cout << "\nAssigning the Subtraction function to basicPtr: " << endl;
    basicPtr = &sub;
    cout << "  Calling the function via Pointer: " << endl;
    cout << "  The output of Subtraction(10, 5) is: " << basicPtr(10, 5) << endl;
    
    cout << "\nAssigning the Multpily function to basicPtr: " << endl;
    basicPtr = mul;
    cout << "  Calling the function via Pointer: " << endl;
    cout << "  The output of Multiplication(10, 5) is: " << basicPtr(10, 5) << endl;

	// End of Program
	return 0;
}

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }