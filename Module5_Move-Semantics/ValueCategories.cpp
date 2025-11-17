/*
    Understanding L-values, R-values, and References in C++
    -------------------------------------------------------

    Key Concepts:
    1. L-value  --> Has a name and a memory address. Exists beyond a single expression.
       Examples: variables like x, y, z. - they are names and lives long

    2. R-value  --> Temporary value without a name. Dies immediately after the expression.
       Examples: 5, x + y, functionReturningValue()

    Why do we care about value categories ? --> 
        - C++ wants to treat temporary objects differently than normal objects. 
            - But, Why ?
                - Temporaries can be moved --> because they are about to disappear anyway.
                - Named objects must be copied --> because they still exist after the expression.
                    string a = "hello";
                    string b = a;          // must COPY
                    string c = a + "!!";    // temporary --> can MOVE instead of copy
                - Moving is faster than copying

    3. L-value reference (T&)
       - Binds ONLY to L-values. (i.e., It must bind to a named object.)
       - You cannot bind an L-value reference to an R-value.
            int x = 5;
            int& ref = x;   // OK

    4. Const L-value reference (const T&)
       - Can bind to BOTH L-values and R-values.
       - WHY? Because const ensures you cannot modify a temporary.

    5. R-value reference (T&&)
       - Binds ONLY to R-values (temporaries).
       - Introduced in C++11 to support "move semantics" (faster than copying).
            int&& r = 10;     // OK (10 is temporary)
            int&& r2 = x;     // ERROR (x is NOT temporary)
                - C++ says: “Oh! You gave me a temporary object. I can optimize this by moving instead of copying.”

    6. Function Overloading:
       - You can overload based on L-value, const L-value, and R-value references.
       - C++ chooses the best match.

    WHY we need this (The REAL reason)
    Reason 1 — Move semantics:
        You cannot implement move constructor / move assignment without this feature.
            - Move constructors let C++:
            - avoid copying
            - reuse memory/resources
            - boost performance
            - Example:  
                vector<int> v1 = {1,2,3};
                vector<int> v2 = std::move(v1);   // super fast!
                - R-value references (&&) make this possible.
    
    Reason 2 — Avoid unnecessary copies:
        If a temporary is created:
            BankAccount acc = getAccount();
            - Then acc can steal the temporary’s resources instead of copying.
    
    Reason 3 — Important for modern C++ libraries
        STL containers (vector, string, etc.) rely heavily on:
            - move constructor
            - move assignment
            - r-value references
        Without understanding value categories --> you cannot understand modern C++.

*/

#include <iostream>
using namespace std;

// Function that accepts ONLY L-values
void PrintValue(int& x) {
    cout << "Called: PrintValue(int& x) - L-value reference\n";
}

// Function that accepts BOTH (L-values + R-values)
// but only if the R-value version is not available
void PrintValue(const int& x) {
    cout << "Called: PrintValue(const int& x) - const L-value reference\n";
}

// Function that accepts ONLY R-values (temporaries)
void PrintValue(int&& x) {
    cout << "Called: PrintValue(int&& x) - R-value reference\n";
}

int Add(int a, int b) {
    // returns by value - RESULT IS AN R-VALUE
    return a + b;
}

int main() {

    cout << "\n=== L-value Examples ===\n";
    int a = 10;
    int b = 20;

    // a and b are L-values - have names
    PrintValue(a);   // calls L-value version
    PrintValue(b);   // calls L-value version

    cout << "\n=== R-value Examples ===\n";
    PrintValue(5);       // temporary - calls R-value version
    PrintValue(a + b);   // (a+b) is temporary - calls R-value version
    PrintValue(Add(3, 4)); // Add() returns a temporary - calls R-value version

    cout << "\n=== Const L-value Binding Example ===\n";
    const int c = 50;
    PrintValue(c);       // c is L-value - calls const L-value version

    cout << "\n=== Binding R-value Reference Variable ===\n";
    int&& temp = 100; // temporary - allowed
    PrintValue(temp); // temp is now NAME - treated as L-VALUE - calls PrintValue(int&)

    return 0;
}
