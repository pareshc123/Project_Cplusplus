#include <fstream>
#include <iostream>
#include <iomanip>

int main() {
    
    std::ofstream file("vehicle_logs/can/huge_log.log");
    if (!file) {
        std::cerr << "Failed to create huge_log.log\n";
        return 1;
    }

    // Write ~5MB of realistic CAN log data
    for (int i = 0; i < 150000; ++i) {  // 3500 lines approx 5MB
        file << "2026-02-20 19:45:"
            << std::setfill('0') << std::setw(2) << (12 + i % 50) << '.'
            << std::setw(3) << (100 + i % 900) << " CAN1 "
            << "ID=" << std::hex << std::setw(8) << std::setfill('0')
            << (0x18DAF110 + i % 100) << " DLC=8 "
            << "DATA=";

        // Fake hex data
        for (int j = 0; j < 8; ++j) {
            file << std::hex << std::setw(2) << std::setfill('0')
                << ((i + j * 17) % 256) << " ";
        }
        file << '\n';
    }

    file.close();
    std::cout << "Created huge_log.log (~5MB) for testing!\n";
    return 0;
}
