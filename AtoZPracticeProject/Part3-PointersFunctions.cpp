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
		
		void execute(int (*operation)(int, int)) {
			int result = operation(10, 5);
		}

		execute(add);  // call it;

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