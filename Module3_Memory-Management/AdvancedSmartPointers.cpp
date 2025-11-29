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



int main() {

    // ===== EXERCISE 9: ECU FACTORY + unique_ptr =====
    cout << "\n===== EXERCISE 9: ECU FACTORY + unique_ptr =====\n";


    // ===== EXERCISE 10: CAN DECODER + shared_ptr =====
    cout << "\n===== EXERCISE 10: CAN DECODER + shared_ptr =====\n";


    // ===== EXERCISE 11: weak_ptr CYCLE BREAKING =====
    cout << "\n===== EXERCISE 11: weak_ptr CYCLE BREAKING =====\n";


    // ===== EXERCISE 12: SENSOR BUFFER (unique_ptr[]) =====
    cout << "\n===== EXERCISE 12: SENSOR BUFFER (unique_ptr[]) =====\n";


    cout << "\n===== END OF ADVANCED EXERCISES =====\n\n";

    // End of Program
    return 0;
}