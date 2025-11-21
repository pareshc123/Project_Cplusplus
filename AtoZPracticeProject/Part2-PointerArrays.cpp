/*

	PART 2 — Pointers + Arrays

		Array decay to pointer
		Pointer indexing
		Pointer arithmetic
		Passing arrays to functions using pointers
		2D arrays and pointers (static vs dynamic)

----------------------------------------------------------
1. ARRAY DECAY — Array name becomes a pointer
----------------------------------------------------------

	When you use an array in an expression, it automatically
	"decays" into a pointer to its first element.

	That means:
		array name  -->  &array[0]  (address of the first element)

	Example:

		int rpm[3] = {1000, 2000, 3000};

		cout << rpm;        // prints address of first element (0x7ffe...)
		cout << &rpm[0];    // same address
		cout << *rpm;       // first element -> 1000

	Expression         Meaning
	-----------------------------------------------------
	rpm                pointer to first element (&rpm[0])
	&rpm[0]            address of first element
	*rpm               first element (same as rpm[0])

----------------------------------------------------------
2. POINTER ARITHMETIC — moves by size of the data type
----------------------------------------------------------

	Pointer arithmetic moves in steps of the data type size,
	NOT in bytes.

	If int is 4 bytes:

		ptr + 1   moves ahead by 4 bytes
		ptr + 2   moves ahead by 8 bytes

	Example:

		int rpm[3] = {1000, 2000, 3000};
		int* ptr = rpm;   // array -> pointer

		cout << ptr[0];       // *ptr        -> 1000
		cout << ptr[1];       // *(ptr + 1)  -> 2000
		cout << ptr[2];       // *(ptr + 2)  -> 3000

	Because:
		ptr[i]  ===  *(ptr + i)

----------------------------------------------------------
3. PASSING ARRAYS TO FUNCTIONS USING POINTERS
----------------------------------------------------------

	When you pass an array to a function, you really pass
	a pointer to its first element.

	Both are the same:

		void checkRPM(int* arr) { ... }
		void printRPM(int rpm[], int size) { ... }

	Inside both functions:
	   arr   --> pointer to first element (&rpm[0])

----------------------------------------------------------
4. STATIC (TRUE) 2D ARRAYS — continuous memory
----------------------------------------------------------

	Example:
		int multiArray[3][4];

	This creates ONE continuous memory block:

	   Row0: [a00][a01][a02][a03]
	   Row1: [a10][a11][a12][a13]
	   Row2: [a20][a21][a22][a23]

	multiArray:
		- is NOT an int**
		- it is a pointer to the FIRST ROW
		- each ROW is an array of 4 integers

	Therefore, a pointer that matches a ROW is:

		int (*multiArrayPtr)[4] = multiArray;

	Meaning:
		multiArrayPtr         = pointer to row 0
		multiArrayPtr + 1     = pointer to row 1
		multiArrayPtr + 2     = pointer to row 2

		*(multiArrayPtr + i)         = ith row (array of 4 ints)
		*(*(multiArrayPtr + i) + j)  = element [i][j]

----------------------------------------------------------
5. 2D ARRAY USING ARRAY OF POINTERS — dynamic rows (staircase)
----------------------------------------------------------

	Here, each row is separately allocated:

		int* arrayPtr[3];   // 3 row pointers

		for (int i = 0; i < 3; ++i) {
			arrayPtr[i] = new int[4];   // each row has 4 columns
		}

	Layout (not continuous):

		arrayPtr[0] -> [x x x x]
		arrayPtr[1] -> [x x x x]
		arrayPtr[2] -> [x x x x]

	Properties:
		- not continuous in memory
		- rows can have different sizes
		- must delete each row manually

----------------------------------------------------------
6. FULLY DYNAMIC 2D ARRAY — int** (pointer to pointer)
----------------------------------------------------------

	int** arr creates a "pointer to pointers":

		int** arr = new int*[3];  // 3 row pointers

		for (int i = 0; i < 3; i++) {
			arr[i] = new int[4];  // each row has 4 columns
		}

	Meaning:
		arr       -> pointer to row pointers
		arr[i]    -> pointer to row i
		arr[i][j] -> element (ith row, jth column)

	Properties:
		- slowest (scattered memory)
		- most flexible (rows can differ)
		- very common in dynamic memory problems
		- NOT compatible with static 2D arrays

----------------------------------------------------------

*/


#include <iostream>
#include <random>

using namespace std;

void printECUBlock(int* block, int size);

int getRandomValue(int& minValue, int& maxValue) {

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(minValue, maxValue);
	return dist(gen);
}

int* getMaxPtr(int* array, int size);

int main() {

	//  ------  Exercise1: Print all array values using a pointer (no indexing)  -------
	cout << "Exercise1: Print all array values using a pointer (no indexing):" << endl;
	int arr1[5] = { 90, 92, 94, 96, 99 };
	int* arr1Ptr = arr1;

	for (int i = 0; i < 5; ++i) {
		cout << *(arr1Ptr + i) << ", ";
	}
	cout << endl;


	//  ------  Exercise2: Modify array values using a pointer  -------
	cout << "\nExercise2: Modify array values using a pointer:" << endl;

	cout << "Before: ";
	for (int i = 0; i < 5; ++i) {
		cout << *(arr1Ptr + i) << " ";
	}
	cout << endl;

	// Modifying the values: 
	for (int i = 0; i < 5; ++i) {
		arr1Ptr[i] = *(arr1Ptr + i) + 10;
	}

	cout << "After: ";
	for (int i = 0; i < 5; ++i) {
		cout << *(arr1Ptr + i) << " ";
	}
	cout << endl;


	//  ------  Exercise3: Find max & min using pointers  -------
	cout << "\nExercise3: Find max & min using pointers:" << endl;
	int rpm[6] = { 800, 1200, 1500, 3000, 2500, 1000 };
	int* rpmPtr = rpm;

	int max = 0;
	int min = 99999;

	for (int i = 0; i < 6; ++i) {

		if (max < *(rpmPtr + i)) {
			max = *(rpmPtr + i);
		}
		if (min > *(rpmPtr + i)) {
			min = *(rpmPtr + i);
		}
	}
	cout << "Max rpm: " << max << ", Min rpm: " << min << endl;


	//  ------  Exercise4: Count how many values exceed a threshold  -------
	cout << "\nExercise4: Count how many values exceed a threshold (85 degrees):" << endl;
	const int size = 15;
	int minValue = 70;
	int maxValue = 100;
	int tempArray[size];
	int* tempArrayPtr = tempArray;


	for (int i = 0; i < size; ++i) {      // Generate Array with random numbers between range
		tempArrayPtr[i] = getRandomValue(minValue, maxValue);
	}

	cout << "Print randomly generated Array between minValue, maxValue(70, 100): ";
	for (int i = 0; i < size; ++i) {
		cout << *(tempArrayPtr + i) << " ";
	}
	cout << endl;

	int tempcounter = 0;

	for (int i = 0; i < size; ++i) {
		if ( *(tempArrayPtr + i) >= 85) {
			tempcounter += 1;
		}
	}

	cout << "Temperature exceeded " << tempcounter << " times." << endl;


	//  ------  Exercise5: Reverse an array using pointers (no indexing!)  -------
	cout << "\nExercise5: Reverse an array using pointers (no indexing!):" << endl;
	cout << "Ex 5.1: Index + counter based: " << endl;
	const int rsize = 9;
	int rArray[rsize];
	int* rArrayPtr = rArray;

	for (int i = 0; i < rsize; ++i) {     // Array with random numbers between 0 and 99
		rArrayPtr[i] = rand() % 100;
	}

	cout << "Generate random numbers between 0 and 99 for rArray: " << endl;
	for (int i = 0; i < rsize; ++i) {
		cout << *(rArrayPtr + i) << " ";
	}
	cout << endl;

	cout << "Start reversing the rArray: " << endl;
	int counter = rsize - 1;

	for (int i = 0; i < (rsize / 2); ++i) {

		int temp1 = *(rArrayPtr + counter);
		*(rArrayPtr + counter) = *(rArrayPtr + i);
		*(rArrayPtr + i) = temp1;
		counter -= 1;
	}

	cout << "Reversed Array (rArray): " << endl;
	for (int i = 0; i < rsize; ++i) {
		cout << *(rArrayPtr + i) << " ";
	}
	cout << endl;

	cout << "\nEx 5.2: True Pointer based reverse uisng two pointers: " << endl;
	cout << "Currently Reversed Array (rArray): " << endl;
	for (int i = 0; i < rsize; ++i) {
		cout << *(rArrayPtr + i) << " ";
	}
	cout << endl;

	cout << "Moving it back to original state ... " << endl;
	int* left = rArray + 0;    // points to first address
	int* right = rArray + rsize - 1;   // points to last address

	while (left < right) {
		int temp = *left;
		*left = *right;
		*right = temp;

		left++;
		right--;
	}

	cout << "New Reversed Array (rArray) using two pointers: " << endl;
	for (int i = 0; i < rsize; ++i) {
		cout << *(rArrayPtr + i) << " ";
	}
	cout << endl;


	//  ------  Exercise6: Function that accepts array using pointer  -------
	cout << "\nExercise6: Function that accepts array using pointer:" << endl;
	int ECUblockArray[5] = { 1, 2, 3, 4, 5 };
	printECUBlock(ECUblockArray, 5);
	cout << endl;

	//  ------  Exercise7: Write a function that returns a pointer to the highest value  -------
	cout << "\nExercise7: Write a function that returns a pointer to the highest value:" << endl;
	const int arrsize = 10;
	int array[arrsize];
	int* arrPtr = array;

	for (int i = 0; i < arrsize; ++i) {   // generate array with random integers
		arrPtr[i] = rand() % 100;
	}

	int* maxPtrValue = getMaxPtr(arrPtr, arrsize);
	cout << "The Highest value returned is: " << *maxPtrValue << endl;

	//  ------  Exercise8: Pointer to multidimensional array  -------
	cout << "\nExercise8: Pointer to multidimensional array:" << endl;
	int map[2][3] = {
	{10, 20, 30},
	{40, 50, 60}
	};

	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 3; ++j) {

			cout << *(*(map + i) + j) << " ";
			//cout << map[i][j] << " "; 
		}
	}
	cout << endl;

	// End of Program
	return 0;
}

void printECUBlock(int* block, int size) {

	// print the loop
	cout << "Array passed using pointer inside the function: ";
	for (int i = 0; i < size; ++i) {
		cout << *(block + i) << " ";
	}
}

int* getMaxPtr(int* array, int size) {

	int* maxPtrValue = array + 0;  // assigning the pointer the first value of array

	cout << "The Array Before: ";
	for (int i = 0; i < size; ++i) {
		cout << *(array + i) << " ";
	}
	cout << endl;

	cout << "Getting the Maximum value ..." << endl;
	for (int i = 0; i < size; ++i) {
		
		if (*maxPtrValue < *(array + i)) {

			maxPtrValue = array + i;    // we want the address of the max value
		}
	}

	return maxPtrValue;
}