#include <iostream>
#include "ECUDataBuffer.h"
using namespace std;

// Function that returns a temporary (R-value)
ECUDataBuffer generateTempBuffer()
{
    ECUDataBuffer temp(1000);  // large temporary buffer
    return temp;               // returns an R-value (temporary) --> triggers MOVE
}

int main()
{
    cout << "\n--- Creating Buffer A (Parametrized constructor) ---\n";
    ECUDataBuffer A(500);

    cout << "\n--- Creating Buffer B using COPY CONSTRUCTOR ---\n";
    ECUDataBuffer B = A;   // copy

    cout << "\n--- Creating Buffer C using MOVE CONSTRUCTOR ---\n";
    ECUDataBuffer C = generateTempBuffer();  // move

    cout << "\n--- Assigning B = A (COPY ASSIGNMENT) ---\n";
    B = A;

    cout << "\n--- Assigning C = generateTempBuffer() (MOVE ASSIGNMENT) ---\n";
    C = generateTempBuffer();

    cout << "\n--- End of Program: Destructors will run for A, B, C ---\n";

    size_t Value = C.GetPtrValue();
    cout << "The Buffer size value for is: " << Value << endl;
    C.SetPtrValue(5000);
}
