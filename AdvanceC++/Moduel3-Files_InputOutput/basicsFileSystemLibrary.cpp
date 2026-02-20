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

#include<iostream>
#include<string>
#include<vector>
#include<filesystem>

using namespace std;
namespace fs = std::filesystem;


void ex1PathIntelligenc(fs::path dir) {

	cout << "The Full Path is: " << dir << endl;
	cout << "The File fullName is: " << dir.filename() << endl;
	cout << "The File extension is: " << dir.extension() << endl;
	cout << "The File stem is: " << dir.stem() << endl;
	cout << "The File Parent directory is: " << dir.parent_path() << endl;
	cout << "The New file Name is: " << dir.replace_filename("ecu1_2026_02_19_secure.log") << "\n" << endl;

}

void ex2setupLogStructure();

int main() {
	
	cout << "======= Exerice 1: Path Intelligence =======" << endl;
	fs::path path1{"vehicle_logs/can_logs/ecu1_2026_02_19.log"};
	ex1PathIntelligenc(path1);

	cout << "======= Exerice 2: Automotive Log Directory Setup =======" << endl;
	ex2setupLogStructure();

	return 0;

}

void ex2setupLogStructure() {

	// Define the subdirectories under vehicle_logs/
	const vector<string> subdirs = {
		"Vehicle_logs/CAN",
		"Vehicle_logs/UDS",
		"Vehicle_logs/Firmware",
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

}