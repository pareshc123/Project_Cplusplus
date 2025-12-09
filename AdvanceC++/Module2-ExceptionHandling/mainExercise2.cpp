#include <iostream>
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
void testExceptions(int errorType) {

    Resource local("LocalResource");   // will be destroyed during stackwinding

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

    std::cout << "\n=== MULTIPLE CATCH BLOCKS + STACK UNWINDING DEMO ===\n" << std::endl;

    for (int error = 0; error <= 3; ++error) {

        try {
            std::cout << "\n ==== Calling Exceptions (" << error << ") ====\n";
            testExceptions(error);
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

    return 0;
}