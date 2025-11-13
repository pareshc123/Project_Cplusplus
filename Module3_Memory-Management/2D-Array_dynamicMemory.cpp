/*
    Dynamic Memory Allocation for 2D Arrays in C++
    
    Description:
    This program demonstrates how to dynamically allocate and deallocate memory
    for a two-dimensional (2D) array using the 'new' and 'delete' operators in C++.
    
    In this example, we create a 2D array on the heap where each row is represented
    by a separate 1D array. 
         - We first allocate an array of integer pointers, where each pointer represents a row of the 2D array. 
         - Then, for each row pointer, we allocate memory for a 1D array of integers representing the columns.
    
    The program also shows how to initialize and access the array elements using
    standard row-column indexing (arr[row][col]) and how to properly release
    the allocated memory to prevent memory leaks.
    
    Key Concepts:
    - Using 'new' to allocate memory dynamically
    - Representing a 2D array as an array of pointers
    - Accessing elements via double indexing
    - Correct use of 'delete[]' to free dynamically allocated memory
    - Ensuring the number of delete calls matches the number of new calls
    
    Note:
    In modern C++, it is often recommended to use std::vector for dynamic arrays
    since it handles memory management automatically and reduces the risk of leaks.

 */

#include <iostream>
using namespace std;

int main() {

    int rows = 2;
    int cols = 3;

    // Step 1: Allocate memory for an array of integer pointers (rows)
    int** pData = new int* [rows];

    // Step 2: Allocate memory for each row (each with 'cols' integers)
    for (int i = 0; i < rows; i++) {
        pData[i] = new int[cols];
    }

    // Step 3: Initialize the 2D array with some values
    int value = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            pData[i][j] = value++;
        }
    }

    // Step 4: Display the contents of the 2D array
    cout << "2D Array Elements:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << pData[i][j] << " ";
        }
        cout << endl;
    }

    // Step 5: Free the dynamically allocated memory
    for (int i = 0; i < rows; i++) {
        delete[] pData[i];   // Free each row
    }
    delete[] pData;           // Free the array of pointers

    cout << "\nMemory successfully freed!" << endl;

    return 0;
}
