/*
    ADVANCED AUTOMOTIVE SMART POINTER EXERCISES
    --------------------------------------------
    Exercises Covered:
      9. unique_ptr + ECU factory
      10. shared_ptr CAN decoder shared by modules
      11. weak_ptr for breaking cyclic ECU references
      12. unique_ptr[] sensor buffer

*/

#include <iostream>
#include <memory>
#include <string>

using namespace std;

// Exercise 9
class ECU {
public:

    string name = "";
    int id = 101;

    ECU() {
        cout << "Default ECU object [" << name << "] created." << endl;
    }

    ECU(string n, int i) : name(n), id(i) {
        cout << "Parametrized ECU object [" << name << "] with ID: [" << id <<  "] created." << endl;
    }

    ~ECU() {
        cout << "ECU Object [" << name << "] Destroyed." << endl;
    }
};

class ECUFactory {
    
    /*
        Factory is a stateless utility class: 
        In embedded automotive, factories usually have no state --> they only create objects.
        Because a "factory" class often:
            has no member variables
            has no state
            is used only as a utility class
    */

public: 
    static unique_ptr<ECU> create(string name, int id) {
        return make_unique<ECU>(name, id);
    }
};

int main() {

    // ===== EXERCISE 9: ECU FACTORY + unique_ptr =====
    cout << "\n===== EXERCISE 9: ECU FACTORY + unique_ptr =====\n";
    // No need to instantiate the factory
    auto engineECU = ECUFactory::create("EngineECU", 100);
    auto brakeECU = ECUFactory::create("BrakeECU", 200);
    auto bcmECU = ECUFactory::create("BCM_ECU", 300);

    // ===== EXERCISE 10: CAN DECODER + shared_ptr =====
    cout << "\n===== EXERCISE 10: CAN DECODER + shared_ptr =====\n";


    // ===== EXERCISE 11: weak_ptr CYCLE BREAKING =====
    cout << "\n===== EXERCISE 11: weak_ptr CYCLE BREAKING =====\n";


    // ===== EXERCISE 12: SENSOR BUFFER (unique_ptr[]) =====
    cout << "\n===== EXERCISE 12: SENSOR BUFFER (unique_ptr[]) =====\n";


    cout << "\n===== END OF ADVANCED EXERCISES =====\n\n";
    cout << "\nEnd of main()" << endl; 
    cout << "   ECUs objects will now be destroyed automatically.\n";

    // End of Program
    return 0;
}