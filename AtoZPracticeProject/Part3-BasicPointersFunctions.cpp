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
int divi(int a, int b);

// Function pointer passed as an argument
int executeOperation(int a, int b, int (* const operationPtr)(int, int));
// const ensures the callback cannot be reassigned inside the function.


// Functions that returns a Function pointers
int (*getOperator(char op))(int, int);

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

	//  ------  Exercise2: Pass Function Pointer to Another Function:  -------
	cout << "\nExercise2: Pass Function Pointer to Another Function:" << endl;
	cout << "Result for addition: " << executeOperation(20, 8, add) << endl;
	cout << "Result for subtraction: " << executeOperation(20, 8, sub) << endl;
	cout << "Result for multiplication: " << executeOperation(20, 8, mul) << endl;

	//  ------  Exercise3: Array of Function Pointer:  -------
	cout << "\nExercise3: Array of Function Pointer:" << endl;
	int (*arrayFuncPtr[4])(int, int) = {add, sub, mul, divi};
	
	int userChoice;
	cout << "Please Enter the choice of arithmetic operation required: " << endl;
	cout << "  0 = Addition, 1 = Subtraction, 2 = Multiply, 3 = Division" << endl;
	cin >> userChoice;
	
	if (userChoice >= 4) {
		cout << "User Choice Incorrect. Please try again." << endl;
		return 0;
	}

	int result = arrayFuncPtr[userChoice](10, 5);
	switch (userChoice) {
	case 0: cout << "Addition request was initiated. The result for the user input is: " << result << endl; break;
	case 1: cout << "Subtraction request was initiated. The result for the user input is: " << result << endl; break;
	case 2: cout << "Multiplication request was initiated. The result for the user input is: " << result << endl; break;
	case 3: cout << "Division request was initiated. The result for the user input is: " << result << endl; break;
	}

	//  ------  Exercise4: Functions that returns a Function Pointer:  -------
	cout << "\nExercise4: Functions that returns a Function Pointer:" << endl;
	char userOpChoice;
	cout << "Please Enter the choice of arithmetic operation required: " << endl;
	cout << "  + = Addition, - = Subtraction, * = Multiply, / = Division" << endl;
	cin >> userOpChoice;

	// function call
	auto returnfuncPtr = getOperator(userOpChoice);
	int resultfuncPtr = returnfuncPtr(10, 5);

	cout << "Result of user Choice of operation '" << userOpChoice << "' is: " << resultfuncPtr << endl;

	// End of Program
	return 0;
}

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }
int divi(int a, int b) {

	if (b == 0) {
		cout << "Division not possible, denominator is 0" << endl;
		return -1;
	}
	else {
		return a / b;
	}

}

int (*getOperator(char op))(int, int) {

	switch (op) {
	case '+': cout << "Addition operation was requested." << endl; return add;
	case '-': cout << "Subtraction operation was requested." << endl; return sub;
	case '*': cout << "Multiplication operation was requested." << endl; return mul;
	case '/': cout << "Division operation was requested." << endl; return divi;
	default: cout << "Invalid input, returning add()\n" << endl;  return add;
	}
}

int executeOperation(int a, int b, int (* const operationPtr)(int, int)) {

	return operationPtr(a, b);
}
