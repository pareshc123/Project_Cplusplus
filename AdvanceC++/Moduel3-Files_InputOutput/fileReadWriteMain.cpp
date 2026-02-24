/*
    Demonstration of Writing an Integer to a Binary File in C++

    Example:
        int x = 25;

    Memory Representation:

        When the program runs, the integer variable x is stored in RAM.
        Assume the address of x is 0x1000.

        On a typical little-endian system, memory will look like:

            Address     Data (1 byte each)
            0x1000      00011001   (25 in binary)
            0x1001      00000000
            0x1002      00000000
            0x1003      00000000

        Since an int is usually 4 bytes, the value 25 occupies 4 bytes in memory.

    ############################# Writing to a Binary File in C++ #############################

        file.write((char*)&x, sizeof(x));

        Explanation:

        1. &x
           Gets the memory address where x is stored, but treat it as a pointer to single bytes (raw byte)
            note: here raw bytes are 00011001 00000000 00000000 00000000

        2. (char*)&x
           Casts the address to a pointer to raw bytes (char*),
           allowing access to memory byte-by-byte.

           Why cast to (char*) ?
            Reason: file.write() works with bytes. A char in C++ is exactly 1 byte.
            We are only telling the compiler: "Don’t think of this as an int anymore. Think of it as 4 separate bytes."
                 - int* moves 4 bytes at a time i.e., move pointer by +1, you jump 4 bytes.
                 - char* moves 1 byte at a time i.e., move pointer by +1, you jump 1 byte.

        3. sizeof(x)
           Tells the program to copy 4 bytes (size of int).

        The program copies the 4 raw bytes starting at the address of x
        and writes them directly into the file.

    Important Concept:

        - We are NOT writing the address of x.
        - We are writing the VALUE stored at that address.
        - Binary writing copies raw memory bytes without conversion.
        - Text writing converts numbers into human-readable ASCII characters.

    Why This Matters:

        This concept is fundamental in:
            - Embedded systems
            - Firmware storage
            - Automotive ECUs
            - Memory dumping
            - Cybersecurity and reverse engineering

        Understanding the difference between value and address
        is essential for low-level programming.

    #############################  Text File Writing in C++  #############################

    Example:
        int x = 25;
        file << x;

    What Happens Internally:

        When writing to a text file using the insertion operator (<<),
        the integer value is converted into a human-readable string.

        The number 25 becomes the characters:
            '2' and '5'

        These characters are stored using ASCII encoding:

            '2' --> 00110010
            '5' --> 00110101

        So the text file stores 2 bytes:
            00110010 00110101

    Key Difference from Binary Writing:

        Text Mode:
            - Converts numbers to characters.
            - Stores human-readable data.
            - Requires formatting and conversion.
            - Slightly slower due to conversion overhead.

        Binary Mode:
            - Writes raw memory bytes directly.
            - No conversion performed.
            - Faster and used in embedded systems.

    When to Use Text Files:

        - Logging
        - Configuration files
        - Debugging output
        - Data meant to be read or edited by humans

    Important Concept:

        Even in text files, data is still stored as binary at the hardware level.
        The difference is that text files store the ASCII representation of numbers,
        not their direct memory representation.

    In embedded and automotive systems, binary format is preferred
    because hardware operates directly on raw bytes.

    #############################  TYPICAL EMBEDDED EXAMPLE  #############################

    #define SENSOR_REGISTER 0x40001000 
    *(volatile uint32_t*)SENSOR_REGISTER
    
    Imagine HW already has memory at fixed address
    Address 0x40001000

    Inside a microcontroller, that address might control:

        - A temperature sensor
        - A CAN controller
        - A GPIO pin
        - A hardware timer

    That address is not normal RAM: It is a hardware register.

    NOW EXPLANTION FOR, *(volatile uint32_t*)SENSOR_REGISTER

    1. *(volatile uint32_t*)SENSOR_REGISTER == *(volatile uint32_t*)0x40001000
        - Treat the number 0x40001000 (SENSOR_REGISTER) as if it is a pointer to a 32-bit unsigned integer(uint32_t*)
    
    2. IGNORE VOLATILE for a moment: 
        - *(uint32_t*)0x40001000 == derefrencing pointer     --> de
        - Go to that address and access what is stored there.
            - Example: int x = 30; 
                       *p = &x 
                       cout << *p;    // 30

    3. What About volatile?
        - volatile uint32_t* --> This memory can change at any time, outside of your program.
        - Because hardware may change it.
        - Example: A sensor updates its value automatically.

        - If you don’t use volatile, the compiler might:

            - Read the value once
            - Store it in a register
            - Never check memory again

        - That would break hardware communication.
        - So volatile tells the compiler:
            - Always read from memory. Never assume it stays the same.

*/
	
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

using std::cout;

fs::path BASE_DIR{ "vehicle_logs" };


int main() {

    cout << "========== Exericse1: Byte-Level Writer ==========\n";
    fs::path file = BASE_DIR / "bytes.bin";

    std::ofstream output1{ file, std::ios::binary };
    if (!output1.is_open()) {
        std::cout << "Cannot open file for writing\n";
        return -1;
    }

    output1.put(0x01);   // put() writes 1 byte only
    output1.put(0x02);
    output1.put(0x03);
    output1.put(0xFF);
    int x = 255;
    output1.put(x); 
    output1.put(0x12345678);  // Wrong outputs --> 120
    
    /*
        In hex: 12 34 56 78
        In dec: 305419896

        But remember:
            put() only writes 1 byte.
            So what does it take?  --> It takes the lowest 8 bits only.
            Lowest byte of: 0x12345678 is 0x78
        when converted to dec we get --> 
            7 × 16 = 112
            8 = 8
            112 + 8 = 120

        ******************  Hence, FINAL RULES  ******************  
            Writing 1 single byte	         put()
            Writing multiple bytes	         write()
            Writing formatted text	         <<

    */

    output1.close();

    std::ifstream input1{ file, std::ios::binary };
    if (!input1.is_open()) {
        std::cout << "Cannot open file for reading\n";
        return -1;
    }

    int byte;
    while ((byte = input1.get()) != EOF) {
        std::cout << byte << "\n";
    }

    input1.close();


    cout << "\n========== Exercise 2 - Seek & Patch ==========\n";
    fs::path file2 = BASE_DIR / "bytes1.bin";

    // Step 1: Create and write 10 integers
    std::ofstream output2(file2, std::ios::binary);
    if (!output2.is_open()) {
        std::cout << "Cannot open file for writing\n";
        return -1;
    }

    int numbers[10] = { 10,20,30,40,50,60,70,80,90,100 };

    for (int i = 0; i < 10; i++) {
        output2.write(reinterpret_cast<char*>(&numbers[i]), sizeof(int));
    }

    output2.close();

    // Step 2: Reopen file for update (read + write)
    std::fstream fileio(file2, std::ios::binary | std::ios::in | std::ios::out);
    if (!fileio.is_open()) {
        std::cout << "Cannot open file for patching\n";
        return -1;
    }

    // Modify the 5th integer (index 4)
    int newValue = 999;

    std::streampos offset = 4 * sizeof(int);
    fileio.seekp(offset);

    fileio.write(reinterpret_cast<char*>(&newValue), sizeof(int));

    fileio.close();

    // Step 3: Read everything back
    std::ifstream input2(file2, std::ios::binary);
    if (!input2.is_open()) {
        std::cout << "Cannot open file for reading\n";
        return -1;
    }

    int value;
    while (input2.read(reinterpret_cast<char*>(&value), sizeof(int))) {
        std::cout << value << "\n";
    }

    input2.close();

    cout << "\n========== Exericse1: ==========";


    cout << "\n========== Exericse1: ==========";

    return 0;
}