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
#include<cstdint>
#include<iomanip>
#include<iostream>
#include<filesystem>

using std::cout;
using std::cin;
using std::endl;
namespace fs = std::filesystem;


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


void ex1PathIntelligenc(fs::path dir) {

	cout << "The Full Path is: " << dir << endl;
	cout << "The File fullName is: " << dir.filename() << endl;
	cout << "The File extension is: " << dir.extension() << endl;
	cout << "The File stem is: " << dir.stem() << endl;
	cout << "The File Parent directory is: " << dir.parent_path() << endl;
	cout << "The New file Name is: " << dir.replace_filename("ecu1_2026_02_19_secure.log") << "\n" << endl;

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


void ex3IterateOverDirectory(fs::path dir) {

	if (!fs::exists(dir) || !fs::is_directory(dir)) {
		cout << "[ERROR] Directory doesnt exists: " << dir << "\n" << endl;
		return;
	}

	int count = 0;

	for (const auto& file : fs::directory_iterator(dir)) {

		if (file.path().extension() == ".log") {
			cout << "[Processing] " 
				 << file.path().filename() 
				 << ", File Size: " << fs::file_size(file)

				 << endl;
			++count;
		}
		else if (file.path().extension() == ".exe") {
			cout << "[Warning] Unknown file identified " << file.path().filename() << endl;
		}
	}

	cout << "Total log files processed: " << count << "\n" << endl;
}


bool ex4isSafeSize(const fs::path& file, std::uintmax_t maxSize) {

	std::error_code ec;

	// Get file size safely (non-throwing)
	std::uintmax_t size = fs::file_size(file, ec);

	if (ec) {
		// File doesn't exist or access denied --> safe by default
		cout << "[INFO]  Cannot read " << file << ": "
			 << ec.message() << endl;
		return true;
	}

	// Check if oversized
	if (size > maxSize) {
		std::cout << "[WARNING] OVERSIZED:  " << file
			<< "(" << size << " bytes > " << maxSize << " bytes)\n";
		return false;
	}

	std::cout << "[OK]  " << file << " (" << size << " bytes) \n";
	return true;

}

// Convenience wrapper for 1MB limit
bool ex4isSafeLogFile(const fs::path& file) {

	/*
		1B = 8 bits (2^3),
		1KB (Kilo-Bytes) = 1024 (2^10),
		1MB (Mega-Bytes) = 1024KB = 1024 * 1024 (2^20),
		1GB (Giga-Bytes) = 1024MB = 1024 * 1024 * 1024 (2^30)
		
		constexpr = "Compile-time constant". The compiler calculates it at compile time, not runtime.
		Benefits:
			- Faster (no runtime calculation)
			- Type safer (compiler checks math)
			- Optimizer friendly
	*/

	constexpr std::uintmax_t ONE_MB = 1024 * 1024;
	return ex4isSafeSize(file, ONE_MB);
}


struct AuditResult {
	size_t totalFiles = 0;
	size_t totalDirs = 0;
};

void ex5AuditScanner(const fs::path& dir, AuditResult& result) {

	if (!fs::exists(dir) || !fs::is_directory(dir)) {
		cout << "[ERROR] Directory doesnt exists: " << dir << "\n" << endl;
		return;
	}

	std::error_code ec;

	// Recursive scan with skip_permission_denied
	for (auto it = fs::recursive_directory_iterator(dir, fs::directory_options::skip_permission_denied, ec); 
				it != fs::recursive_directory_iterator(); ++it) {

		const auto& entry = *it;
		const auto& path = entry.path();

		// Skip if error occurred
		if (ec) {
			std::cout << "[SKIP] " << path << ": " << ec.message() << '\n';
			ec.clear();
			it.increment(ec);  // Skip this entry
			continue;
		}

		// Print formatted audit info
		if (entry.is_directory()) {
			std::cout << "[DIR ] " << std::left << std::setw(50) << path
				<< " (directory)" << '\n';
			++result.totalDirs;
		}
		else if (entry.is_regular_file()) {
			std::uintmax_t size = fs::file_size(path, ec);
			std::cout << "[FILE] " << std::left << std::setw(50) << path
				<< "(" << size << " bytes)\n";
			++result.totalFiles;
		}
		else {
			std::cout << "[OTHER] " << std::left << std::setw(50) << path
				<< "(symlink/special)" << '\n';
		}
	}
}


int main() {
	
	cout << "======= Exerice 1: Path Intelligence =======" << endl;
	std::string filename = getFileWithCurrentTimeStamp("ECUID-1", ".log");
	fs::path path1{"vehicle_logs/can_logs/" + filename};
	ex1PathIntelligenc(path1);

	cout << "======= Exerice 2: Automotive Log Directory Setup =======" << endl;
	ex2setupLogStructure();

	cout << "======= Exerice 3: Iterate Over Directory =======" << endl;
	fs::path path2 = { "Vehicle_logs/CAN" };
	ex3IterateOverDirectory(path2);

	cout << "======= Exerice 4: File Size Protection Check =======" << endl;
	// Test small files (safe)
	ex4isSafeLogFile("vehicle_logs/CAN/frame1.log");     // ~1KB --> OK
	ex4isSafeLogFile("vehicle_logs/CAN/frame2.log");     // ~1KB --> OK
	ex4isSafeLogFile("vehicle_logs/CAN/notes.txt");      // ~300B --> OK

	// Test non - existent(safe)
	ex4isSafeLogFile("vehicle_logs/CAN/missing.log");

	// Test oversized (WARNING)
	ex4isSafeLogFile("vehicle_logs/CAN/huge_log.log");   // >1MB --> WARNING
	cout << endl;

	cout << "======= Exerice 5 - Recursive Audit Scanner =======" << endl;
	AuditResult result;
	fs::path root = "vehicle_logs";
	ex5AuditScanner(root, result);
	std::cout << "\n=== AUDIT SUMMARY ===\n";
	std::cout << "Total Files: " << result.totalFiles << '\n';
	std::cout << "Total Dirs:  " << result.totalDirs << '\n';
	std::cout << "Total Items: " << (result.totalFiles + result.totalDirs) << '\n';

	return 0;

}

