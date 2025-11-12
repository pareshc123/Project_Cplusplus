/*
    ----------------------------------------------------------------------
    NAMESPACE IN C++

    A namespace is a named scope that groups related code elements (like functions, classes, variables, etc.) together.

    Purpose:
        1. Prevent name clashes — Two functions or classes can have
           the same name if they are in different namespaces.
        2. Improve code organization — Group related functionality
           under a meaningful namespace name (e.g., Math, Sort, Graphics).
        3. Control visibility — Code inside a namespace is not
           visible outside unless explicitly accessed.

    Basic Syntax:
        namespace MyNamespace {
            void myFunction();
            int value;
        }

    Accessing Members:
        1. Using full-qualified name:
              MyNamespace::myFunction();
        2. Using a 'using' declaration (for specific types):
              using MyNamespace::myFunction;
              myFunction();  // Direct use
        3. Using a 'using namespace' directive (opens all names):
              using namespace MyNamespace;
              myFunction();  // All names visible
           Warning: Avoid this in large projects (may cause name clashes).

    Nested Namespaces:
        namespace Outer {
            namespace Inner {
                void hello();
            }
        }
        // Access using Outer::Inner::hello();

    Unnamed (Anonymous) Namespace:
        namespace {
            void internalHelper();
        }
        // Visible only within this translation unit (source file).
        // Used for file-scope functions and variables.

    Best Practices:
        - Use namespaces to logically group related code.
        - Avoid `using namespace std;` in header files.
        - Prefer explicit namespace usage (e.g., std::cout) in real projects.
    ----------------------------------------------------------------------
*/

#include <iostream>
#include <vector>

using namespace std;

namespace MathLib {

    // -------------------------------
    //  BASIC OPERATIONS
    // -------------------------------
    namespace Basic {

        double Add(double x, double y) {
            return x + y;
        }

        double Subtract(double x, double y) {
            return x - y;
        }

        double Multiply(double x, double y) {
            return x * y;
        }

        double Divide(double x, double y) {
            if (y != 0) {
                return x / y;
            }
            else {
                std::cerr << "Error: Division by zero!" << std::endl;
                return 0;
            }
        }
    }
    // -------------------------------
    //  ADVANCED OPERATIONS
    // -------------------------------

    namespace Advanced {

        double Power(double base, int exponent) {
            double result = 1;
            for (int i = 0; i < exponent; ++i) {
                result *= base;
            }
            return result;
        }

        double SquareRoot(double value) {
            if (value >= 0) {
                return std::sqrt(value);
            }
            else {
                std::cerr << "Error: Negative input for square root!" << std::endl;
                return 0;
            }
        }

        // Nested Helper namespace (internal utilities)
        namespace Helper {

            // Compare two numbers with small tolerance
            bool Compare(double a, double b, double tolerance = 1e-9) {
				return std::fabs(a - b) < tolerance;
            }
        }

        double Mean(const std::vector<double>& data) {

            if (data.empty()) {
                std::cerr << "Error: Empty data set!" << std::endl;
                return 0;
			}
            double sum = 0;
            for (double val : data) sum += val;
            return sum / data.size();
        }

        double Variance(const std::vector<double>& data) {
            if (data.size() < 2) {
                std::cerr << "Error: Insufficient data for variance!" << std::endl;
                return 0;
			}
            double mean = Mean(data);
            double variance = 0;
            for (double val : data)
                variance += pow(val - mean, 2);
            return variance / data.size();

        }
	}
}

int main() {

    // Using fully qualified names
    double a = 10, b = 5;
    cout << "Add: " << MathLib::Basic::Add(a, b) << endl;
    cout << "Subtract: " << MathLib::Basic::Subtract(a, b) << endl;
    cout << "Multiply: " << MathLib::Basic::Multiply(a, b) << endl;
    cout << "Divide: " << MathLib::Basic::Divide(a, b) << endl;

    // Work with Advanced namespace
    vector<double> nums = { 2, 4, 4, 4, 5, 5, 7, 9 };

    cout << "\nMean: " << MathLib::Advanced::Mean(nums) << endl;
    cout << "Variance: " << MathLib::Advanced::Variance(nums) << endl;

    // Using nested Helper namespace directly
    bool areClose = MathLib::Advanced::Helper::Compare(0.3000000001, 0.3);
    cout << "\nCompare(0.3000000001, 0.3) --> " << (areClose ? "True" : "False") << endl;

    // You can shorten access with 'using' if needed
    using MathLib::Basic::Add;
    cout << "\nUsing declaration for Add --> " << Add(100, 200) << endl;

    return 0;
}