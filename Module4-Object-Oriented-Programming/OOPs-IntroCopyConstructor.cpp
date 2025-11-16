/*
    C++ Copy Constructor
    -------------------

    A **Copy Constructor** in C++ is a special constructor used to create a new object
    as a copy of an existing object. It initializes the new object using the values of
    an existing object of the same class.

    Syntax:
        ClassName(const ClassName& other);
    
    WHY DO WE NEED A COPY CONSTRUCTOR?
    --------------------------------------
    If your class contains a pointer / dynamic memory / resources --> default copying will be WRONG.
        Example:
            int* ptr1 = new int(10);
            int* ptr2 = ptr1;   // copies the address --> both point to same memory
                 - This is a shallow copy --> copies only the pointer address.

        Problems:
            Problem 1: Double delete
                 - Both objects will call delete pointer --> crash (in debug mode).
            Problem 2: Changing one object changes the other
                 - Because both contain SAME pointer.
    
    More Explanation ahead in detail.
    
    Key Points:
    1. It is automatically invoked in these scenarios:

       a) When an object is **initialized from another object** at declaration:
            Integer i1(10);
            Integer i2 = i1;   // copy constructor

       b) When an object is **passed by value** into a function:
            void print(Integer obj);  // creates a copy!

       c) When a function **returns an object by value**:
            Integer getNumber() {
                Integer temp(20);
                return temp;   // returns a copy
            }

    2. If you **do not define a copy constructor**, the compiler generates a default one.
       The default copy constructor performs a **shallow copy**, which means it copies
       member variables **as they are**, including pointer addresses.

        2.A) Shallow Copy Problem:
           - If your class has **pointer members**, a shallow copy will copy the address, not the actual data.
           - Both objects now point to the same memory.
           - Deleting one object or modifying the pointer can cause crashes or unexpected behavior.

        2.B) Deep Copy:
           - A **deep copy** creates a **new memory allocation** and copies the data, not just the pointer.
           - This ensures each object manages its own memory safely.

    3. Rule of Three:
       - If your class manages dynamic memory (or other resources), you should define:
             a) Destructor
             b) Copy Constructor
             c) Copy Assignment Operator
       - This avoids memory leaks and shallow copy issues.
 
    ------------------------------------------
*/

// Example 1: Copy Constructor with Deep Copy

#include <iostream>
using namespace std;

class Integer {
    int* value;

public:
    // Default constructor
    Integer(int val = 0) {
        value = new int(val);
    }

    // Copy Constructor (deep copy)
    Integer(const Integer& other) {
        value = new int(*(other.value)); // allocate new memory and copy value
    }

    // Destructor
    ~Integer() {
        delete value;
        value = nullptr;
    }

    // Getter
    int getValue() const { 
        return *value; 
    }

    // Setter
    void setValue(int val) { *value = val; }
};

int main() {
    Integer num1(100);
    Integer num2 = num1;  // Invokes copy constructor (deep copy)

    cout << "Num1: " << num1.getValue() << endl;
    cout << "Num2: " << num2.getValue() << endl;

    num2.setValue(200);

    cout << "After modifying num2:" << endl;
    cout << "Num1: " << num1.getValue() << endl; // remains 100
    cout << "Num2: " << num2.getValue() << endl; // now 200

    return 0;
}


/*
    Explanation:
    - num1 and num2 each have their **own copy of memory**.
    - Modifying num2 does not affect num1, unlike shallow copy.

    6. Important Notes:
       - Always pass the parameter **by reference** in the copy constructor to avoid
         infinite recursion.
         Example:
             ClassName(const ClassName& other);  // correct
             ClassName(const ClassName other);    // wrong, creates copy --> infinite loop
       - Use `const` when possible to ensure the original object is not modified:
             ClassName(const ClassName& other);

    Summary:
    - **Purpose:** To safely create a copy of an object.
    - **Shallow vs Deep copy:** Deep copy required if object manages dynamic memory.
    - **Rule of Three:** If using dynamic memory, define Destructor, Copy Constructor,
      and Copy Assignment Operator.
    - **When invoked:** Object initialization, passing by value, returning by value.
*/
