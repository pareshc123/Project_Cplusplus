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

#include<string>
#include<vector>
#include<cstdint>
#include<fstream>
#include<iostream>

#include"fileOperations.h"

using std::cout;
using std::cin;
using std::endl;


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
		"vehicle_logs/CAN",
		"vehicle_logs/UDS",
		"vehicle_logs/Firmware",
		"vehicle_logs/ECU-Logs",
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


struct secureDeleteResult {
	size_t totalFiles = 0;
};


void ex6deleteOldLogs(const fs::path& dir, secureDeleteResult& result) {

	if (!fs::exists(dir) || !fs::is_directory(dir)) {
		cout << "[ERROR] Directory doesnt esists: " << dir << endl;
		return;
	}

	std::error_code ec;
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

		// Scanning for log files:
		if (entry.is_regular_file() && path.extension() == ".log") {
			++result.totalFiles;
			fs::remove(path, ec);
			if (!ec && !fs::exists(path)) {
				cout << "[DELETED] " << "Successfully deleted File \"" << path.filename() << "\"" << endl;
			}
			else {
				cout << "[FAILED] " << "Failed to delete File \"" << path.filename() << "\": " 
					<< ec.message() << endl;
			}
			ec.clear();   // reset for the next file
		}
	}
}


bool rotateLogIfNeeded(const fs::path& logFile, std::uintmax_t maxSizeKB = 500) {

	std::error_code ec;

	// Check if file exists
	if (!fs::exists(logFile, ec)) {
		std::cout << "[INFO] Log file doesn't exist: " << logFile.filename() << '\n';
		return false;
	}

	// Current Size
	std::uintmax_t size = fs::file_size(logFile, ec);
	if (ec) {
		std::cerr << "[ERROR] Cannot read size: " << ec.message() << '\n';
		return false;
	}

	std::uintmax_t maxSizeBytes = maxSizeKB * 1024;

	if (size > maxSizeBytes) {
		cout << "[ROTATE] " << logFile.filename()
			<< " (" << size << " bytes > " << maxSizeBytes << " bytes) \n";

		// Generate backup name: frame.log --> frame_backup_1.log
		fs::path backupFile = logFile.parent_path() /
			(logFile.stem().string() + "_1" + logFile.extension().string());

		// Rename (atomic operation)
		fs::rename(logFile, backupFile, ec);
		if (ec) {
			std::cerr << "[ERROR] Rename failed: " << ec.message() << '\n';
			return false;
		}

		std::cout << "[OK] Renamed to: " << backupFile.filename() << '\n';

		// Create fresh empty log
		std::ofstream newLog(logFile);
		if (newLog) {
			newLog.close();
			std::cout << "[OK] Created fresh log: " << logFile.filename() << '\n';
			return true;
		}
		else {
			std::cerr << "[ERROR] Failed to create new log\n";
			return false;
		}
	}
	std::cout << "[OK] Log safe: " << logFile.filename()
		<< " (" << size << " bytes < " << maxSizeBytes << " bytes)\n";
	return true;

}

// Convenience function for default 500KB
bool checkAndRotate(const fs::path& logFile) {
	return rotateLogIfNeeded(logFile, 500);  // 500 KB
}

int main() {
	
	//cout << "======= Exerice 1: Path Intelligence =======" << endl;
	//std::string filename = getFileWithCurrentTimeStamp("ECUID-1", ".log");
	//fs::path path1{"vehicle_logs/can_logs/" + filename};
	//ex1PathIntelligenc(path1);

	//cout << "======= Exerice 2: Automotive Log Directory Setup =======" << endl;
	//ex2setupLogStructure();

	//cout << "======= Exerice 3: Iterate Over Directory =======" << endl;
	//fs::path path2 = { "vehicle_logs/CAN" };
	//ex3IterateOverDirectory(path2);

	//cout << "======= Exerice 4: File Size Protection Check =======" << endl;
	//// Test small files (safe)
	//ex4isSafeLogFile("vehicle_logs/CAN/frame1.log");     // ~1KB --> OK
	//ex4isSafeLogFile("vehicle_logs/CAN/frame2.log");     // ~1KB --> OK
	//ex4isSafeLogFile("vehicle_logs/CAN/notes.txt");      // ~300B --> OK

	//// Test non - existent(safe)
	//ex4isSafeLogFile("vehicle_logs/CAN/missing.log");

	//// Test oversized (WARNING)
	//ex4isSafeLogFile("vehicle_logs/CAN/huge_log.log");   // >1MB --> WARNING
	//cout << endl;

	//cout << "======= Exerice 5 - Recursive Audit Scanner =======" << endl;
	//AuditResult result;
	//fs::path root = "vehicle_logs";
	//ex5AuditScanner(root, result);
	//std::cout << "\n=== AUDIT SUMMARY ===\n";
	//std::cout << "Total Files: " << result.totalFiles << '\n';
	//std::cout << "Total Dirs:  " << result.totalDirs << '\n';
	//std::cout << "Total Items: " << (result.totalFiles + result.totalDirs) << '\n' << endl;

	//cout << "======= Exerice 6 - Secure Deletion System =======" << endl;
	//secureDeleteResult result2;
	//fs::path root2 = "vehicle_logs";
	//ex6deleteOldLogs(root2, result2);
	//std::cout << "\n=== SECURE DELETION SUMMARY ===\n";
	//std::cout << "Total log Files deleted: " << result2.totalFiles << '\n' << endl;
	

	cout << "======= Exercise 7 - MINI Log Rotation System =======" << endl;
	fs::path logFile1 = fs::path("vehicle_logs/CAN") / getFileWithCurrentTimeStamp("CANframe", ".log");

	// Test 1: Small file (safe)
	createCANFrameLog(logFile1, 200);
	checkAndRotate(logFile1);

	// Test 2: Make it huge first
	std::cout << "\[TEST] Creating huge CANframe.log...\n";
	
	fs::path logFile2 = fs::path("vehicle_logs/CAN") / getFileWithCurrentTimeStamp("CANframe", ".log");
	createCANFrameLog(logFile2, 15000);
	checkAndRotate(logFile2);

	// Test 3: Now rotate!
	checkAndRotate(logFile2);

	return 0;

}

