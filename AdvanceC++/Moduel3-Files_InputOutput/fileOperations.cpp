#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "fileOperations.h"

void createCANFrameLog(fs::path& filePath, std::uintmax_t fileSizeKB) {
    
    std::ofstream file(filePath);
    if (!file) {
        std::cerr << "[ERROR] Failed to create file \"" << filePath.filename() << "\" at " << filePath << "\n";
        return;
    }

    // Write realistic CAN log data
    for (int i = 0; i < fileSizeKB; ++i) {  // 3500 lines approx 5MB
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
    std::cout << " [INFO] Created file \"" << filePath.filename() 
              << " (" << (fs::file_size(filePath)) <<  " bytes)\" at " << filePath << "\n";
 
}

std::string getFileWithCurrentTimeStamp(const std::string& prefix,
    const std::string& extension) {

    using namespace std::chrono;

    // get current time as time_t
    auto now = system_clock::now();

    std::time_t t = system_clock::to_time_t(now);

    // convert to local time
    std::tm local{};

#ifdef _WIN32  // <-- This macro is defined on ALL Windows platforms
    localtime_s(&local, &t);  // Windows (32-bit or 64-bit)
#else
    localtime_r(&t, &local);  // Linux/Mac
#endif


    // Format: YYYY-MM-DD_HH-MM-SS
    std::ostringstream oss;

    oss << prefix << '_'
        << std::put_time(&local, "%Y-%m-%d_%H-%M-%S")
        << extension;

    return oss.str();

}