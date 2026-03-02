#pragma once
#include <filesystem>

namespace fs = std::filesystem;

// Declaration for file operations
void createCANFrameLog(fs::path& filePath, std::uintmax_t fileSizeKB = 500);
std::string getFileWithCurrentTimeStamp(const std::string& prefix, const std::string& extension);