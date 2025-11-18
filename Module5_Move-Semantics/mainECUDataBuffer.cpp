/*
    This program demonstrates COPY SEMANTICS and MOVE SEMANTICS in C++
    using an ECUDataBuffer class that simulates a dynamically allocated
    ECU (Engine Control Unit) data buffer.

    -----------------------
    WHY THIS EXAMPLE EXISTS
    -----------------------
     
    ECUDataBuffer internally manages:
        - a raw pointer (int* dataPtr)
        - dynamically allocated memory
        - a buffer size

    Whenever a class manages resources manually (like memory),
    the C++ compiler will NOT safely auto-generate copy/move functions. Hence we must folow "RULE OF 5"
    Therefore, we MUST define: 

        1. Copy Constructor
        2. Copy Assignment Operator
        3. Move Constructor
        4. Move Assignment Operator
        5. Destructor

    These functions prevent dangerous shallow copies and ensure
    memory is moved or copied safely.

    Note:
        - If your class does NOT own a resource, define nothing --> compiler handles it (Rule of Zero)

    -------------------------
    COPY vs MOVE (Simplified)
    -------------------------

    COPY semantics:
        - Used when the source is an L-value (a named object).
        - The buffer is duplicated --> new memory is allocated.
        - More expensive.

    MOVE semantics:
        - Used when the source is an R-value (temporary or std::move).
        - The buffer is *stolen*, no deep copy.
        - Leaves source safe and empty.
        - Much faster.

    ------------------------
    WHAT THE MAIN() SHOWS
    ------------------------

    1. Creating buffer A            --> calls parametrized constructor
    2. Copying A into B             --> calls COPY constructor
    3. Moving temporary into C      --> calls MOVE constructor
    4. Assigning (copy) B = A       --> calls COPY assignment
    5. Assigning (move) C = temp    --> calls MOVE assignment

    The console will clearly show which function was triggered
    by printing messages such as:
        [Copy Constructor]
        [Move Constructor]
        [Copy Assignment]
        [Move Assignment]

    This helps visualize the difference between copy and move behavior.

    Importance of std::move:
    - It simply casts an L-value into an R-value reference.
    - So the move constructor or move assignment is chosen instead of a copy (even for an L-Value).

        Without this cast:
            L-values --> always uses copy constructor (and never uses move which is fast and efficient)
            R-values --> move constructor

        But if you want to move from an L-value, you MUST use std::move.

    Example:
        ECUDataBuffer ecu1(100);
        ECUDataBuffer ecu2 = ecu1;   // --> copy (slow)
        
        You wanted to MOVE buf1 into buf2, BUT compiler chooses copy because buf1 is an L-value.
        So you must write:
            
            ECUDataBuffer ecu2 = std::move(ecu1);  // --> move (fast)
            
            - Now the move constructor runs instead of copy

*/

#include <iostream>
#include "ECUDataBuffer.h"

using namespace std;

int main()
{
    cout << "\n--- Creating ECUDataBuffer - Parametrized constructor ---" << endl;
    ECUDataBuffer ecu1(500);

    cout << "\n--- Creating mulitple CANFrames to add them to buffer ---" << endl;
    const CANFrame f1(0x153, 8, { 0x01, 0x04, 0x19, 0x98, 0x30, 0x11, 0x19, 0x98});
    const CANFrame f2(0x122, 8, { 0x15, 0x08, 0x20, 0x19, 0x31, 0x12, 0x20, 0x30});

    cout << "User-Defined CAN Frame f1 generated: " << f1.toString() << endl;
    cout << "User-Defined CAN Frame f2 generated: " << f2.toString() << endl;

    const CANFrame f3 = CANFrame::generateRandomFrame();
    const CANFrame f4 = CANFrame::generatePatternFrame();

    std::cout << "CAN Frame f3 generated with Random generator: " << f3.toString() << endl;
    std::cout << "CAN Frame f4 generated with Pattern geneartor: " << f4.toString() << endl;

    cout << "\n--- Adding CANFrames to CANbufferList in ECU via OpsOverloading += ---" << endl;
    for (const auto& f : { f1, f2, f3, f4 })
        ecu1 += f;

    cout << "\n--- Get complete CANbufferList from ECU via OpsOverloading << ---" << endl;
    cout << ecu1;

    cout << "\n--- Indexing CANFrames from CANbufferList in ECU via OpsOverloading [] ---" << endl;
    ecu1[2];

    cout << "\n--- End of Program: Destructors will be inititated for all the ECU and CAN objects---\n" << endl;

    // End of program
    return 0;

}
