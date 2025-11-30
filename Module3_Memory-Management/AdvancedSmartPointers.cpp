/*
    ADVANCED AUTOMOTIVE SMART POINTER EXERCISES
    --------------------------------------------
    Exercises Covered:
      9. unique_ptr + ECU factory
      10. shared_ptr CAN bus shared by modules
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


// Exercise 10
class CANBus {
public:
    void send(int id) {
        cout << "(id = 0x" << hex << id << ") sending CAN Frame" << endl;
    }

    ~CANBus() {
        cout << "CANBus destroyed\n";
    }
};

// Software Modueles
class EngineModule {

    shared_ptr<CANBus> bus;
public:
    EngineModule(shared_ptr<CANBus> bus) : bus(bus) {
    }

    void process() {
        cout << "   Engine module ";
        bus->send(0x100);
    }
};

class ABSModule {
    shared_ptr<CANBus> bus;

public:
    ABSModule(shared_ptr<CANBus> bus) : bus(bus){}

    void process() {
        cout << "   ABS module: ";
        bus->send(0x200);
    }

};

class TransmissionModule {
    shared_ptr<CANBus> bus;

public:
    TransmissionModule (shared_ptr<CANBus> bus) : bus(bus) {}

    void process() {
        cout << "   Transmission module: ";
        bus->send(0x300);
    }

};

// Exercise 11
class ECUCycle {
public:
    int id;
    weak_ptr<ECUCycle> peer;  // weak reference prevents cycle

    ECUCycle(int id) : id(id) {
        cout << "ECU " << hex << id << " created\n";
    }

    ~ECUCycle() {
        cout << "ECU " << hex << id << " destroyed\n";
    }
};


int main() {

    // ===== EXERCISE 9: ECU FACTORY + unique_ptr =====
    cout << "\n===== EXERCISE 9: ECU FACTORY + unique_ptr =====\n";
    // No need to instantiate the factory
    auto engineECU = ECUFactory::create("EngineECU", 100);
    auto brakeECU = ECUFactory::create("BrakeECU", 200);
    auto bcmECU = ECUFactory::create("BCM_ECU", 300);


    // ===== EXERCISE 10: CAN bus + shared_ptr =====
    cout << "\n===== EXERCISE 10: CAN bus + shared_ptr =====\n";
    auto CANSharedPtr = make_shared<CANBus>();

    // Create Modules that share ownership
    EngineModule eng(CANSharedPtr);
    TransmissionModule transmission(CANSharedPtr);
    ABSModule abs(CANSharedPtr);

    cout << "Reference count after module creation: "
        << CANSharedPtr.use_count() << endl;

    // Simulate CAN message Processing
    eng.process();
    transmission.process();
    abs.process();

    cout << "Reference count at end of main: "
        << CANSharedPtr.use_count() << endl;


    // ===== EXERCISE 11: weak_ptr CYCLE BREAKING =====
    cout << "\n===== EXERCISE 11: Breaking ECU Cycle with weak_ptr =====\n";
    // Create two ECUs with shared_ptr
    shared_ptr<ECUCycle> ecuA = make_shared<ECUCycle>(0x101);
    shared_ptr<ECUCycle> ecuB = make_shared<ECUCycle>(0x202);

    // Cross-link using weak_ptr
    ecuA->peer = ecuB;
    ecuB->peer = ecuA;

    // Print use_count() – should remain 1 each
    cout << "ECU A use_count: " << ecuA.use_count() << endl;
    cout << "ECU B use_count: " << ecuB.use_count() << endl;


    // ===== EXERCISE 12: SENSOR BUFFER (unique_ptr[]) =====
    cout << "\n===== EXERCISE 12: SENSOR BUFFER (unique_ptr[]) =====\n";


    cout << "\n===== END OF ADVANCED EXERCISES =====\n\n";
    cout << "\nEnd of main()" << endl; 
    cout << "All the objects will be destroyed automatically.\n";

    // End of Program
    return 0;
}