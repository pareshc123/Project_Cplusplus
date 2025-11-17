/*
	This is the main file. It will
		create several CAN frames using CANFrame Class
		push them into the container
		call overloaded operators to do some operations
		print results
*/

#include "CANFrame.h"

int main() {

	// CAN Frame
	CANFrame f1(0x100, 3, { 0x11, 0x22, 0x33, 0,0,0,0,0 });
	CANFrame f2(0x200, 2, { 0xAA, 0xBB, 0,0,0,0,0,0 });

	cout << f1.toString() << "\n";
	cout << f2.toString() << "\n";

}