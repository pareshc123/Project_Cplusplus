/*
	Reference.cpp

	A reference is essentially an alias for another variable. 

		int x = 10;      // normal variable
		int& ref = x;    // ref is a reference to x

		- It is not a new variable; it’s just another name for the same memory location.
		- Any changes made through the reference affect the original variable.
		- A reference must always be initialized when declared.
		- Once bound to a variable, it cannot be changed to refer to another variable.

	Notes: 
		
		* References cannot be null (Unlike pointers, references must always refer to a valid variable.)
		* References are safer than pointers for most cases where you just need to alias a variable.
		* Use cases:
			- Function parameters (pass by reference)
			- Returning values from functions without copying
			- Modifying variables indirectly
*/

#include <iostream>

using namespace std;

int main() {

	// A randowm variable
	int var{ 50 };

	// Creating a reference to var (an alias)
	int& refvar = var;

	cout << "Current Value of var: " << var << endl;
	cout << "Current Value of reference refvar: " << refvar << endl;

	cout << "\n";

	cout << "Current Address of var: " << &var << endl;
	cout << "Current Address of reference refvar: " << &refvar << endl;

	// Modifying the value using the reference
	refvar = 100;
	cout << "\nNew value of var after modifying through reference: var: " << var << endl;
	cout << "New Value of reference after modifying through reference: refvar: " << refvar << endl;

	// Modifying the value using the variable
	refvar = 200;
	cout << "\nNew value of var after modifying through reference: var: " << var << endl;
	cout << "New Value of reference after modifying through reference: refvar: " << refvar << endl;

	cout << "\n";

	cout << "Current Address of var after modification: " << &var << endl;
	cout << "Current Address of reference refvar after modification: " << &refvar << endl;

	// End of Program
	return 0;
}