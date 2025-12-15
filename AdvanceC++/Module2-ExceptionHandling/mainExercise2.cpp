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



// EXERCISE 1 — Basic multiple exception types
void testSimpleExceptions(int errorType) {

    Resource local("LocalResource");   // destroyed during stack unwinding

    if (errorType == 1) throw std::runtime_error("Runtime Error Occurred!");
    if (errorType == 2) throw std::logic_error("Logic Error Occurred!");
    if (errorType == 3) throw "Unknown C-style exception!";

    std::cout << "No exception thrown.\n";
}



// EXERCISE 2 — Raw pointers DO NOT get cleaned on exception
void testRawPointerExceptions(int errorType, bool& destroyedCorrectly) {

    Resource* test = new Resource("PointerResource");

    if (errorType == 1) throw std::runtime_error("Runtime Error Occurred!");
    if (errorType == 2) throw std::logic_error("Logic Error Occurred!");
    if (errorType == 3) throw "Unknown C-style exception!";

    destroyedCorrectly = true;
    delete test;
}



// EXERCISE 3 — Smart pointers ensure cleanup even during exceptions
void testSmartPointerException(int errorType) {

    Resource local("LocalResource");

    auto safePtr1 = std::make_unique<Resource>("HeapResource1");
    auto safePtr2 = std::make_unique<Resource>("HeapResource2");

    if (errorType == 1) throw std::runtime_error("Runtime Error Occurred!");
    if (errorType == 2) throw std::logic_error("Logic Error Occurred!");
    if (errorType == 3) throw "Unknown C-style exception!";

    std::cout << "No exception thrown.\n";
}



int main() {

    std::cout << "\n=== EXERCISE 1: MULTIPLE CATCH BLOCKS + STACK UNWINDING ===\n";

    for (int err = 0; err <= 3; ++err) {

        try {
            std::cout << "\n--- Calling testSimpleExceptions(" << err << ") ---\n";
            testSimpleExceptions(err);
        }
        catch (const std::runtime_error& e) {
            std::cout << "[CATCH] Runtime Error: " << e.what() << '\n';
        }
        catch (const std::logic_error& e) {
            std::cout << "[CATCH] Logic Error: " << e.what() << '\n';
        }
        catch (const std::exception& e) {
            std::cout << "[CATCH] std::exception: " << e.what() << '\n';
        }
        catch (...) {
            std::cout << "[CATCH] Unknown exception\n";
        }
    }



    std::cout << "\n\n=== EXERCISE 2: RAW POINTER LEAK DEMONSTRATION ===\n";

    bool destroyedCorrectly = false;

    try {
        testRawPointerExceptions(1, destroyedCorrectly);
    }
    catch (...) {
        std::cout << "[CATCH] Exception caught.\n";
    }

    if (!destroyedCorrectly)
        std::cout << "PointerResource NOT destroyed --> Memory leaked!\n";
    else
        std::cout << "PointerResource destroyed --> No leak.\n";



    std::cout << "\n\n=== EXERCISE 3: SMART POINTER SAFE CLEANUP ===\n";

    try {
        testSmartPointerException(1);
    }
    catch (const std::runtime_error& e) {
        std::cout << "[CATCH] Runtime Error: " << e.what() << '\n';
    }

    return 0;
}