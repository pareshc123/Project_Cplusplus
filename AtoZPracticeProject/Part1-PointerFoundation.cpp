/*
	Pointer Foundations
*/


#include <iostream>

using namespace std;

int main() {

	//  ------  Exercise1: Basic Pointer setup:  -------
	cout << "Exercise1: Basic Pointer setup:";
	int rpm = 1500;
	int* rpmPtr = &rpm;
	
	cout << "Value of rpm: " << rpm << endl;
	cout << "Address of rpm: " << &rpm << endl;
	cout << "Value of rpmPtr: " << rpmPtr << endl;
	cout << "The dereferenced pointer value: " << *rpmPtr << endl;


	//  ------  Exercise2: Modify a variable through pointer  -------
	cout << "\nExercise2: Modify a variable through pointer:" << endl;
	int speed = 50;
	cout << "Initialized speed value: " << speed << endl;

	int* speedPtr = &speed;
	*speedPtr = 120;
	cout << "Modified speed value: " << speed << endl;



	//  ------  Exercise3: Pointer Safety Check  -------
	cout << "\nExercise3: Pointer Safety Check:" << endl;
	int* randomPtr;
	// cout << "Random Ptr value: " << randomPtr << endl;  // Commented this line because of build error
	cout << "Build not possible. Error C4700 Uninitialized local variable 'randomPtr' used" << endl;



	//  ------  Exercise4: Null Pointer Initialization  -------
	cout << "\nExercise4: Null Pointer Initialization:" << endl;
	int* nullPtr = nullptr;
	cout << "Print the nullPtr: " << nullPtr << endl;
	if (nullPtr != nullPtr){}
	else {
		cout << "Pointer 'nullPtr is null.'" << endl;
	}


	//  ------  Exercise5: ECU Sensor Example  -------
	cout << "\nExercise5: ECU Sensor Example:" << endl;
	int oiltemp = 90;
	cout << "Current Value of oiltemp: " << oiltemp << endl;

	int* oiltempPtr = &oiltemp;
	cout << "Increase oil temperature through pointer using expression *oiltempPtr += 10: " << endl;
	*oiltempPtr += 10;
	cout << "New Value of oiltemp: " << oiltemp << endl;


	//  ------  Exercise6: Swap Two Variables using Pointers  -------
	cout << "\nExercise6: Swap Two Variables using Pointers:" << endl;
	int a = 5, b = 10;
	int* ptr1{ &a };
	int* ptr2{ &b };
	cout << "Address of ptr1 and ptr2 after initialization {ptr1: " << ptr1 << ", ptr2: " << ptr2 << endl;
	cout << "value stored at ptr1 and ptr2 before swap {ptr1: " << *ptr1 << ", ptr2: " << *ptr2 << endl;
	
	int temp = *ptr1;
	
	*ptr1 = b;
	*ptr2 = temp;
	cout << "Address of ptr1 and ptr2 after swap {ptr1: " << ptr1 << ", ptr2: " << ptr2 << endl;
	cout << "value stored at ptr1 and ptr2 after swap {ptr1: " << *ptr1 << ", ptr2: " << *ptr2 << endl;


	//  ------  Exercise7: Pointer to Const  -------
	cout << "\nExercise7: Pointer to Const:" << endl;
	int torque1 = 200;
	int torque2 = 300;
	const int* torquePtr = &torque1;
	cout << "Current Address of ptr & value storead at ptr {Address: " << torquePtr << ", value: " << *torquePtr << endl;
	cout << "Comment: Pointer to const basically means, the value cannot be changed however,\n" 
			"we can change the address at which the pointer is pointing" << endl;
	cout << "hence, expression *torquePtr = 250; should throw error" << endl;
	cout << "But you can assign it to new variable ... " << endl;
	torquePtr = &torque2;
	cout << "New Address of ptr & value storead at ptr {Address: " << torquePtr << ", value: " << *torquePtr << endl;


	//  ------  Exercise8: Const Pointer  -------
	cout << "\nExercise8: Const Pointer:" << endl;
	int torque3 = 200;
	int* const torque3Ptr = &torque3;

	cout << "Current Address of ptr & value storead at ptr {Address: " << torque3Ptr << ", value: " << *torque3Ptr << endl;
	cout << "Comment: Const Pointer basically means, the address at which pointer is poiniting cannot be changed however,\n"
		"we can change the value the pointer is currently storing" << endl;
	cout << "hence, expression *torque3Ptr = &torque4; should throw error" << endl;
	cout << "But you can assign it to new variable and modify it" << endl;
	*torque3Ptr = 300;
	cout << "New Address of ptr & value storead at ptr {Address: " << torque3Ptr << ", value: " << *torque3Ptr << endl;

	//  ------  Exercise9: Pointer to Pointer (Double Pointer)  -------
	cout << "\nExercise9: Pointer to Pointer (Double Pointer):" << endl;
	int x = 100;
	int* intPtr = &x;
	int** ptrIntPtr = &intPtr;
	cout << "Value of x: " << x << endl;
	cout << "Value of intPtr: " << *intPtr << endl;
	cout << "Value of ptrIntPtr: " << **ptrIntPtr << endl;


	//  ------  Exercise10: ECU RAM Block Example  -------
	cout << "\nExercise10: ECU RAM Block Example:" << endl;
	cout << "Reading an ECU block ..." << endl;

	int ramBlock = 555;
	int* diagTool = &ramBlock;

	cout << "ECU RAM read: " << *diagTool << endl;	
	*diagTool = 777;
	cout << "New RAM value: " << ramBlock << endl;

	
	// End of Program
	return 0;
}
