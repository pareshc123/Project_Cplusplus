// capstone_exceptions.cpp

#include <iostream>
#include <string>
#include <memory>
#include <vector>

/*
	================================================================================
    CAPSTONE PROJECT: COMPLETE C++ EXCEPTION HANDLING DEMONSTRATION
    ----------------------------------------------------------------
    This file integrates ALL exception-handling concepts learned so far:

    * Multiple catch blocks
    * Nested try/catch handling
    * Rethrowing exceptions using bare throw
    * Exception modification before rethrow
    * Stack unwinding demonstration
    * Raw pointer memory-leak scenario
    * Smart pointers + RAII for safe cleanup
    * Exceptions in constructors
    * Why destructors must NOT throw
    * The noexcept specifier + noexcept operator
    * Custom exception classes

    PROJECT SCENARIO:
    -----------------
    We simulate a small "Data Ingestion Pipeline" that reads records from a
    file-like source. Some records may be corrupted, unreadable, or missing.
    
    - FileReader constructor may fail     --> throws FileOpenError
    - Record constructor may fail         --> throws BadRecordError
    - Local per-record errors are caught internally (nested exceptions)
    - If too many bad records occur, error is escalated:
            * error message is modified
            * original exception is rethrown using `throw;`
    
    The RecordProcessor class demonstrates:
        -- RAII through smart pointers
        -- Safe destruction during stack unwinding
        -- Correct use of exception propagation and filtering

    Additional demonstrations:
        1. RAW POINTER + EXCEPTION  --> memory leak
        2. noexcept(true) violation --> program aborts
        3. noexcept(false) function
        4. Using noexcept(expression) operator

    PURPOSE:
        This file serves as a complete, cohesive demonstration of modern,
        professional C++ exception-handling techniques.
    ================================================================================

*/

// ----------------------------- Custom Exceptions -----------------------------
struct FileOpenError :public std::runtime_error {
    explicit FileOpenError(const std::string& msg) : std::runtime_error(msg){}
};

struct BadRecordError : public std::runtime_error {

    explicit BadRecordError(const std::string& msg) : std::runtime_error(msg){}

    // Convenience constructor with bad record id
    explicit BadRecordError(int id)
        : std::runtime_error(std::string("BadRecordError: record id=") + std::to_string(id)) {}
};

struct TooManyErrors : public std::runtime_error {
    explicit TooManyErrors(const std::string& msg) : std::runtime_error(msg) {}
};


// ----------------------------- Utility: simple Logger -------------------------
enum class Level {Info, Warn, Error, Security};
void log(Level lvl, const std::string& msg) {

    const char* L = (lvl == Level::Info ? "Info" : lvl == Level::Warn ? "Warn" :
        lvl == Level::Error ? "Error" : "Security");
    
    std::cout << "[" << L << "]" << msg << std::endl;
}

int main() {

    // End of Program
    return 0;
}
