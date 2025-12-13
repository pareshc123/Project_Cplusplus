// capstone_exceptions.cpp

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <random>
#include <chrono>
#include <sstream>

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


// ----------------------------- Random utilities -------------------------------
class Random {

private:
    std::mt19937 eng;
    std::bernoulli_distribution distrBool;

public:
    Random()
        : eng(static_cast<unsigned>(std::chrono::steady_clock::now().time_since_epoch().count())),
        distrBool(0.8)  {}

    // return true (success) or false (failure)
    bool success() { return distrBool(eng); }

    // roll with given probability
    bool roll(double prob) {
        std::bernoulli_distribution d(prob);
        return d(eng);
    }

};


// ----------------------------- Resource for RAII demo -------------------------
class Resource {

private:
    std::string name_;

public:
    explicit Resource(const std::string name) : name_(name) { 
        std::cout << "Resource constructor: " << name_ << std::endl;
    }

    ~Resource() noexcept {
        std::cout << "Resource destructor: " << name_ << std::endl;
    }
};


// ----------------------------- Record --------------------------------
class Record {

private:
    int id_;

public:

    // Constructing a Record may fail (e.g., parse error)
    explicit Record(int id, Random& rd) : id_(id) {

        if (!rd.roll(0.75)) {       // 75% success, 0.25% fail
            throw BadRecordError(id_);
        }

        // Initialization success
    }

    int get_id() const noexcept { return id_; }

};


// ----------------------------- FileReader --------------------------------
class FileReader {

public:
    // Constructor attempts to "open" the file.Simulate failure randomly.
    explicit FileReader(bool simulateFail = false) {
    
        if (simulateFail) {
            throw FileOpenError("Failed to open data source (simulated).");
        }

        log(Level::Info, "FileReader: opened data source successfully.");
    }

    // Destructor must be noexcept
    ~FileReader() noexcept {
        // cleanup resources if any
        log(Level::Info, "[Destructor] FileReader: closed Data source.");
    }

    // Simulate reading a raw record id from source; will return id
    int readRecordId(int index) {

        // For demo: return index(could be anything)
        return index;
    }
};


// ----------------------------- RecordProcessor --------------------------------
class RecordProcessor {

private:
    std::unique_ptr<FileReader> reader_;
    int errorThreshold_;

public:

    explicit RecordProcessor(std::unique_ptr<FileReader> reader, int errorThreshold = 4)
        : reader_(std::move(reader)), errorThreshold_(errorThreshold) 
    {
        if (!reader_) throw FileOpenError("RecordProcessor: invalid FileReader");
    }

    // process `count` records. Demonstrates nested try/catch, rethrow and modification.

    void processRecords(int count) {
        Random rd;
        int errorCount = 0;
        std::vector<std::unique_ptr<Record>> processed;   // keep successfull records (just demo)
        processed.reserve(static_cast<size_t>(count > 0 ? count : 0));

        for (int i = 0; i < count; ++i) {

            // A nested try/catch per-record so we can continue after a failed record.
            try {

                // read raw id (simulate)
                int id = reader_->readRecordId(i);

                // Attempt to construct a Record (may throw BadRecordError)
                // NOTE: constructor may throw; if it does, stack unwinding ensures local objects are cleaned
                auto r = std::make_unique<Record>(id, rd);

                // Record Successfully constructed - add to processed
                processed.push_back(std::move(r));
                log(Level::Info, std::string("Processed Record id = ") + std::to_string(id));
            }
            catch (BadRecordError& ex) {

                // We can handle some record-level locally
                ++errorCount;
                std::ostringstream oss;
                oss << "RecordProcessor: failed to process record " << i << " (" << ex.what() << ")"
                    << " [errorCount=" << errorCount << "]";
                log(Level::Info, oss.str());

                // If too many errors, augment the exception and rethrow to outer scope
                if (errorCount > errorThreshold_) {
                    // Modify the original exception object (caught by reference), then rethrow

                    ex = BadRecordError(std::string("[Escalated] too many bad records; last id = ") + std::to_string(i));
                    throw;  // rethrow original (now modified) exception object
                }

                // else: continue processing other records
            }
            catch (const std::exception& ex) {

                // catch-all for other std::exceptions that might happen during record processing
                ++errorCount;
                log(Level::Error, std::string("RecordProcessor: std::exception while processing: ") + ex.what());

                if (errorCount > errorThreshold_) {
                    // convert to specific escalation and throw
                    throw TooManyErrors("Too many processing errors - aborting processing.");
                }
            }
            // NOTE: no catch(...) here so truly unknown exceptions will propagate
        }

        // Finished processing loop
        std::ostringstream summary;
        summary << "RecordProcessor: completed. Success=" << processed.size() << ", Errors=" << errorCount;
        log(Level::Info, summary.str());

    }
};


// ----------------------------- Small RAW pointer leak demo --------------------
void rawPointerLeakDemo() {

    std::cout << "\n === RAW POINTER LEAK DEMO (do not use in real code) ===\n";

    int* ptr = new int[10];
    std::cout << "Allocated int[10] at " << static_cast<void*> (ptr) << std::endl;

    // Simulate an exception happening *before* delete[] p:
    try {
        throw std::runtime_error("Simulated error before deleting raw pointer");
        delete[] ptr; // never reached
    }
    catch (...) {
        std::cout << "Caught exception - but raw pointer was never deleted -> leak demonstrated\n";
        // Intentionally not deleting p to demonstrate leak (do NOT copy this pattern)
    }
    // In real code, use smart pointers or ensure deletion in catch/finally style
}


// ----------------------------- noexcept demonstration ------------------------
int add_noexcept(int a, int b) noexcept {
    return a + b;
}

int add_may_throw(int a, int b) {
    // trivial but non-noexcept
    return a + b;
}

void noexceptDemo() {
    std::cout << "\n--- noexcept demo ---\n";

    std::cout << "noexcept(add_noexcept): " << std::boolalpha << noexcept(add_noexcept(1, 2)) << "\n";
    std::cout << "noexcept(add_may_throw): " << std::boolalpha << noexcept(add_may_throw(1, 2)) << "\n";

    // Example showing why you should not mark things noexcept unless sure:
    // The following code is *commented* because it will terminate the program:
    //
    // void willTerminate() noexcept { throw std::runtime_error("boom"); }
    // willTerminate(); // calling this will call std::terminate() immediately
    //
    // If you want to experiment, uncomment the two lines above and run the program
    // to observe immediate termination (not catchable).
}


// ----------------------------- main -----------------------------
int main() {

    // End of Program
    return 0;
}
