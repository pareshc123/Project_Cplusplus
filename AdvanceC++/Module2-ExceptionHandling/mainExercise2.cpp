#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

/*
================================================================================
    MULTIPLE CATCH BLOCKS & STACK UNWINDING – EXERCISE NOTES
    --------------------------------------------------------

    This file demonstrates "two core exception-handling concepts" in C++:

    ---------------------------------------------------------------------------
    1. MULTIPLE CATCH BLOCKS
    ---------------------------------------------------------------------------
    A single try-block can throw different *types* of exceptions.
    To handle them properly, C++ allows multiple catch blocks, each matching a
    specific exception type:

        try {
            // code that may fail
        }
        catch (const std::runtime_error& e) { ... }
        catch (const std::logic_error& e)   { ... }
        catch (const std::exception& e)     { ... }  // base class catch
        catch (...) { ... }                  // catch-all (not recommended)

    Key rules:
      * More specific exceptions must appear *first*
      * Base-class catch blocks (catch(std::exception&)) must appear *last*
      * catch(...) should be avoided unless absolutely necessary

    ---------------------------------------------------------------------------
    2. STACK UNWINDING
    ---------------------------------------------------------------------------
    When an exception is thrown, C++ begins *stack unwinding*:

        - It exits the current function immediately.
        - All local objects in that function are destroyed.
        - Their destructors run automatically.
        - Control moves up the call stack until a matching catch is found.

    This ensures:
        * Local objects are destroyed safely
        * Destructor-based cleanup works (RAII)

    BUT:
        X Dynamically allocated memory (new/malloc) is NOT freed automatically
          --> leads to memory leaks
          --> use smart pointers instead

    ---------------------------------------------------------------------------
    WHAT THIS FILE DEMONSTRATES
    ---------------------------------------------------------------------------

    We create a simple class "Resource" that prints messages in constructor
    and destructor so we can visually observe stack unwinding.

    Then we have a function "testExceptions" which may randomly throw:
        - std::runtime_error
        - std::logic_error

    In main(), we use multiple catch blocks to handle them.

    When an exception is thrown:
        1. Resource destructor automatically runs (stack unwinding)
        2. The matching catch block receives the exception

    More Advance version:

    This version also extends the above example by demonstrating how **smart
    pointers automatically free heap memory during stack unwinding** and why raw pointers are troublesome.

    Why smart pointers?
        - If an exception is thrown, the function exits immediately.
        - Raw pointers allocated with `new` are NOT freed automatically (Exercise 2).
        - This leads to memory leaks.

    But with smart pointers (Exercise 3):
        std::unique_ptr<T> ptr(new T(...));

        * Destructor of unique_ptr automatically deletes the object
        * Even when exceptions are thrown
        * Zero memory leaks
        * No need for manual delete

    Demonstrated Concepts:
        1. Multiple catch blocks handling different exception types.
        2. Stack unwinding destroying objects (local + smart pointer managed).
        3. Automatic cleanup of dynamically allocated memory using unique_ptr.

================================================================================
*/

// Class to demonstrate stack unwinding through destructor calls
class Resource {
    
    std::string name;

public:
    Resource(const std::string& name) :name(name) {
        std::cout << "[Resource] Constructor called: " << name << std::endl;
    }

    ~Resource() {
        std::cout << "[Resource] Destructor called: " << name << std::endl;
    }
};

// Function that throws different exception types
void testSimpleExceptions(int errorType) {

    Resource local("LocalResource");   // will be destroyed during stackwinding

    if (errorType == 1)
        throw std::runtime_error("Runtime Error Occurred!");

    if (errorType == 2)
        throw std::logic_error("Logic Error Occurred!");

    if (errorType == 3)
        throw "Unknown C-style exception!";

    std::cout << "No exception thrown.\n";

}


// Function that throws error but destructor not getting deleted
void testRawPointerExceptions(int errorType, bool& flag) {

    Resource *test = new Resource("PointerResource");   // will not be destroyed during stackwinding

    if (errorType == 1)
        throw std::runtime_error("Runtime Error Occurred!");

    if (errorType == 2)
        throw std::logic_error("Logic Error Occurred!");

    if (errorType == 3)
        throw "Unknown C-style exception!";

    std::cout << "No exception thrown.\n";

    flag = true;         // once code is here the flag turns to zero
    delete test;

}

// Function demonstrating stack unwinding + smart pointers
void testSmartPointerException(int errorType)
{
    std::cout << "Creating local Resource on stack...\n";
    Resource local("LocalResource");

    std::cout << "Creating multiple Resource on heap using unique_ptr...\n";
    
    std::unique_ptr<Resource> safePtr1(new Resource("HeapResource1"));
    auto safePtr2 = std::make_unique<Resource>("HeapResource2");
    
    /*
        When an exception is thrown, all the three objects MUST be destroyed :
          * local is destroyed (stack unwinding)
          * safePtr automatically deletes HeapResource
     */

    if (errorType == 1)
        throw std::runtime_error("Runtime Error Occurred!");

    if (errorType == 2)
        throw std::logic_error("Logic Error Occurred!");

    if (errorType == 3)
        throw "Unknown C-style exception!";

    std::cout << "No exception thrown.\n";

}

// Main demonstrating multiple catch blocks + stack unwinding
int main() {

    std::cout << "\n=== EXERCISE1: MULTIPLE CATCH BLOCKS + STACK UNWINDING DEMO ===" << std::endl;

    for (int error = 0; error <= 3; ++error) {

        try {
            std::cout << "\n ==== Calling Exceptions (" << error << ") ====\n";
            testSimpleExceptions(error);
        }
        catch (const std::runtime_error& e) {
            std::cout << "[CATCH] Runtime Error handled: " << e.what() << std::endl;
        }
        catch (const std::logic_error& e) {
            std::cout << "[CATCH] Logic Error handled: " << e.what() << std::endl;
        }
        catch (const std::exception& e) {
            std::cout << "[CATCH] General std::exception handled: " << e.what() << std::endl;
        }
        catch (...) {
            std::cout << "[CATCH] Unknown exception caught!" << std::endl;
        }
    }

    std::cout << "\n\n=== EXERCISE 2: New Pointer + STACK UNWINDING DEMO ===" << std::endl;

    int error = 1;
    bool flag = false;    // if pointer will be deleted, then turn flag True

    try {
        std::cout << "\n ==== Calling Pointer Exceptions (" << error << ") ====\n";
        testRawPointerExceptions(error, flag);
    }
    catch (const std::runtime_error& e) {
        std::cout << "[CATCH] Runtime Error handled: " << e.what() << std::endl;
        
    }
    if (!flag) {
        std::cout << "Class [Resource] Destructor not called. Pointer not Deleted --> Memory leaked!!" << std::endl;
    }
    else {
        std::cout << "Class [Resource] Destructor called. Pointer Deleted --> No Memory leak!!" << std::endl;
    }

    std::cout << "\n\n=== EXERCISE 3: Smart Pointer + STACK UNWINDING DEMO ===" << std::endl;
    int err = 1;

    try {
        std::cout << "\n ==== Calling Pointer Exceptions (" << error << ") ====\n";
        testSmartPointerException(err);
    }
    catch (const std::runtime_error& e) {
        std::cout << "[CATCH] Runtime Error handled: " << e.what() << std::endl;

    }

    return 0;
}