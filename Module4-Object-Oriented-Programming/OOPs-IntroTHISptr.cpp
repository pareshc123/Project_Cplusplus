/*
    C++ 'this' Pointer
    -----------------

    In C++, every non-static member function of a class has an implicit pointer called 'this'.
    When you call a member function on an object, C++ automatically passes a pointer to that object.

    The 'this' pointer points to the current object that is calling the member function.
    It allows the function to access the object's own members and differentiate between member
    variables and parameters with the same name.

    Key Points:
    1. 'this' exists only in non-static member functions because static functions do not belong to any object.
    2. Inside a member function, accessing a member variable like 'name' is equivalent to 'this->name'.
    3. Common uses of 'this' pointer:

       (A) Resolve naming conflicts between member variables and parameters:
           Example:
               class Employee {
                   private:
                       string name;
                   public:
                       void setName(string name) {
                           this->name = name; // member variable = parameter
                       }
               };

       (B) Return the current object to enable **method chaining**:
           Example:
               class Employee {
                   double salary;
               public:
                   Employee& giveRaise(double amount) {
                       salary += amount;
                       return *this; // returns reference to current object
                   }
               };

           Method chaining allows multiple operations on the same object in a single line:
               Employee emp1;
               emp1.giveRaise(2000).giveRaise(3000).giveRaise(5000);

           - Returning *this allows chaining because the first call returns the object itself.
           - Returning void would update the object but **cannot chain** further calls.

       (C) To pass the current object to another function.
          Example:

            void promote() {
                promoteEmployee(this); // send pointer to current object
            }

            void promoteEmployee(Employee* emp) {
                cout << emp->name << " has been promoted!" << endl;
            }

        Explaination:
            'this' is a pointer to the current object (for e.g emp1) that is calling the function.
            If you want to send the current object to another function (here - promoteEmployee()), you can pass 'this'.

       (D) Inside constructors – to clarify that you are assigning to the object's member variables.
            Employee(string name) {
                this->name = name;
            }

    4. Type of 'this' pointer:
       - Inside normal member functions: ClassName* (e.g., Car* this)
       - Inside const member functions: const ClassName* (cannot modify members)
            Example:
                void Display() const {
                    cout << this->name; // read-only access
                }

    Benefits:
    - Helps distinguish object members from local variables or parameters.
    - Enables chaining of functions on the same object.
    - Provides a way to reference the calling object explicitly.
*/

#include <iostream>
#include <string>

using namespace std;

class Employee {
    
private:

    // non-static member initialization
    string name{"Unknown"};
    int id{0};
    double salary{99999};

public:
    // constructor using this to intitialize member variables
    Employee(string name, int id, double salary) {

        this->name = name;     // Left side = the object's member, Right side = function argument
        this->id = id;
        this->salary = salary;
    }

    // Setters using 'this'
    void setName(string name) {
        this->name = name;
    }

    void setSalary(double salary) {
        this->salary = salary;
    }

    // Method returning current object for method chaining
    Employee& giveRaise(double amount) {
        this->salary += amount;
        return *this;         // allows chaining
    }

    // Display function marked const, 'this' becomes const pointer
    void display() const {
        cout << "Name: " << this->name
            << ", ID: " << this->id
            << ", Salary: " << this->salary << endl;
    }

    // Passing current object to another function
    void promote() {
        promoteEmployee(this); // send pointer to current object
    }
    

private:
    // Example function taking an Employee* to show passing 'this'
    void promoteEmployee(Employee* emp) {
        cout << emp->name << " has been promoted!" << endl;
    }

};

int main() {

    Employee emp1("X-Men", 450, 135465);

    // Display details
    emp1.display();

    // Modify using setters
    emp1.setName("Alice Johnson");
    emp1.setSalary(55000);
    emp1.display();

    // Use method chaining with 'this'
    emp1.giveRaise(2000).giveRaise(3000);
    emp1.display();

    // Pass 'this' to a function
    emp1.promote();

    // End of Program
    return 0;
}