/*
	The filesystem library was introduced in C++17 and lives in:

	#include <filesystem>
	namespace fs = std::filesystem;

	It allows you to:

		- Work with paths
		- Create/delete directories
		- Check file existence
		- Get file sizes
		- Iterate through folders
		- Manage logs
		- Validate file integrity

	In automotive & cybersecurity, this is important for:

		- ECU logging systems
		- Secure log storage
		- Firmware update validation
		- Digital forensics tools

*/

#include<chrono>
#include<string>
#include<vector>
#include<sstream>
#include<iostream>
#include<filesystem>

using std::cout;
using std::cin;
using std::endl;
namespace fs = std::filesystem;


void ex1PathIntelligenc(fs::path dir) {

	cout << "The Full Path is: " << dir << endl;
	cout << "The File fullName is: " << dir.filename() << endl;
	cout << "The File extension is: " << dir.extension() << endl;
	cout << "The File stem is: " << dir.stem() << endl;
	cout << "The File Parent directory is: " << dir.parent_path() << endl;
	cout << "The New file Name is: " << dir.replace_filename("ecu1_2026_02_19_secure.log") << "\n" << endl;

}

void ex2setupLogStructure();           // exercise 2: declaration

void ex3IterateOverDirectory() {

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

int main() {
	
	cout << "======= Exerice 1: Path Intelligence =======" << endl;
	std::string filename = getFileWithCurrentTimeStamp("ECUID-1", ".log");
	fs::path path1{"vehicle_logs/can_logs/" + filename};
	ex1PathIntelligenc(path1);

	cout << "======= Exerice 2: Automotive Log Directory Setup =======" << endl;
	ex2setupLogStructure();

	cout << "======= Exerice 3: Iterate Over Directory =======" << endl;
	ex3IterateOverDirectory();

	return 0;

}

void ex2setupLogStructure() {                             // exercise 2: definition

	// Define the subdirectories under vehicle_logs/
	const std::vector<std::string> subdirs = {
		"Vehicle_logs/CAN",
		"Vehicle_logs/UDS",
		"Vehicle_logs/Firmware",
		"Vehicle_logs/ECU-Logs",
	};

	std::error_code ec;

	for (const auto& dir : subdirs) {
		bool created = fs::create_directories(dir, ec);

		if (ec) {
			std::cerr << "[ERROR] Failed to create '" << dir << "': " << ec.message() << endl;
		}
		else if (created) {
			cout << "[OK] Created: " << dir << endl;
		}
		else {
			cout << "[INFO] Already exists: " << dir << endl;
		}
	}

	cout << endl;
}