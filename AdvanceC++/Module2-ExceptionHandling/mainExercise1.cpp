#include <iostream>
#include <limits>
#include <stdexcept>
#include <climits>
#include <cstdlib>


/*
================================================================================
    MEMORY ALLOCATION ERROR HANDLING – EXERCISE NOTES
    -------------------------------------------------

    This exercise demonstrates two different approaches to handling memory
    allocation failures:

        (1) Conventional C-style error handling using malloc() and NULL checks
        (2) Modern C++ exception-based error handling using throw/catch

    ---------------------------------------------------------------------------
    WHY WE USE malloc(ULLONG_MAX)
    ---------------------------------------------------------------------------
    On modern 64-bit systems, requesting a large block of memory using:

        malloc(count * sizeof(int))

    might not fail immediately, because the OS often allocates "virtual memory"
    lazily. This means `malloc()` may return a non-null pointer even though the
    memory cannot actually be used later.

    To force malloc() to fail *immediately*, we intentionally allocate:

        malloc(ULLONG_MAX);

    This requests an impossibly large memory block, causing malloc() to return
    NULL right away. This makes it easy to test our error-handling paths.

    ---------------------------------------------------------------------------
    1. CONVENTIONAL ERROR HANDLING (processRecordsConventional)
    ---------------------------------------------------------------------------
    - We call malloc() and check the result manually.
    - If malloc() returns NULL, the function prints an error message and returns
      an error code (e.g., -1).
    - This is the classic C-style approach.
    - Danger: If the programmer forgets the NULL check, the program may crash
      later when dereferencing the pointer.

    Example:
        ptrArr = (int*) malloc(ULLONG_MAX);
        if (ptrArr == nullptr) {
            // Handle failure manually
        }

    ---------------------------------------------------------------------------
    2. EXCEPTION-BASED HANDLING (processRecordsException)
    ---------------------------------------------------------------------------
    - When malloc() fails, instead of returning an error code we throw a
      std::runtime_error.
    - The function stops executing immediately.
    - Control jumps to the nearest try/catch block.
    - This keeps normal logic clean and moves error-handling to a separate place.

    Example:
        if (ptrArr == nullptr) {
            throw std::runtime_error("Memory Allocation Failed");
        }

    ---------------------------------------------------------------------------
    3. EXCEPTION CAUGHT IN main()
    ---------------------------------------------------------------------------
    The thrown exception is handled in main():

        try {
            processRecordsException(...);
        }
        catch (const std::runtime_error& e) {
            std::cout << e.what();
        }

    - The catch block receives the exception object created by "throw".
    - e.what() prints the message attached to the exception.

    ---------------------------------------------------------------------------
    SUMMARY
    ---------------------------------------------------------------------------
    * malloc(ULLONG_MAX) ensures memory allocation fails reliably
    * Conventional handling requires manual NULL checks
    * Exception handling is cleaner and separates logic from error handling
    * Modern C++ encourages exceptions or smart pointers instead of raw malloc
    * This exercise demonstrates how both techniques behave

================================================================================
*/


// -----------------------------------------------------------------------------
// Conventional C-style error handling
// -----------------------------------------------------------------------------
int processRecordsConventional(int count)
{
    // Force malloc() to fail immediately
    int* ptrArr = static_cast<int*>(malloc(ULLONG_MAX));

    if (ptrArr == nullptr) {
        std::cout << "\nMemory Allocation Failed (Conventional Handling)" << std::endl;
        return -1;  // Error code
    }

    // Process records (won't be reached in this forced-failure example)
    for (int i = 0; i < count; ++i) {
        ptrArr[i] = i + 1;
    }

    free(ptrArr);
    return 0;
}


// -----------------------------------------------------------------------------
// Exception-based error handling
// -----------------------------------------------------------------------------
int processRecordsException(int count)
{
    // Force malloc() to fail immediately
    int* ptrArr = static_cast<int*>(malloc(ULLONG_MAX));

    if (ptrArr == nullptr) {
        throw std::runtime_error("Memory Allocation Failed (Exception Handling)");
    }

    // Process records (won't be reached)
    for (int i = 0; i < count; ++i) {
        ptrArr[i] = i + 1;
    }

    free(ptrArr);
    return 0;
}


// -----------------------------------------------------------------------------
// Main function
// -----------------------------------------------------------------------------
int main()
{
    // Test conventional error handling
    processRecordsConventional(std::numeric_limits<int>::max());

    // Test exception-based handling
    try {
        processRecordsException(std::numeric_limits<int>::max());
    }
    catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}