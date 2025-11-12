/*
	basics of Input and output in C++
*/

#include <iostream>	 // include the input-output stream library
#include <string>    // include the string library for string handling

int main() {
	
	// Output to the console
	std::cout << "Hello, World!" << std::endl; // std::endl inserts a new line
	// Declare a variable to hold user input
	int userInput;
	// Prompt the user for input
	std::cout << "Please enter an integer: ";
	
	// Read input from the user
	std::cin >> userInput;
	// Output the received input
	std::cout << "You entered: " << userInput << std::endl;

	// Character input example
	char userChar;
	std::cout << "Please enter a character: ";
	std::cin >> userChar;
	std::cout << "You entered the character: " << userChar << std::endl;

	// Clear leftover newline before getline
	std::cin.ignore(); // to ignore the newline character left in the buffer

	// String input example
	std::string userString; // array to hold a string input
	std::cout << "Please enter your Fullname: ";
	std::getline(std::cin, userString); // use getline to read a full line including spaces
	std::cout << "You entered the Fullname: " << userString << std::endl;

	// End of the program
	return 0;

}