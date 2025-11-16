#include <iostream>
#include <conio.h>

using namespace std;

int main() {

    // Default position
    int x = 10, y = 10;
    char dir = 'a';

    cout << "\nPress Enter to exit.";

    while (dir != '\r') {  // Enter key = '\r'

        cout << "\nYour current location is: " << x << ", " << y << endl;
        cout << "Enter Direction to get to treasure (n, s, w, e): ";

        dir = _getche();  // Read a key

        if (dir == '\r')  // Exit if Enter pressed
            break;

        switch (dir) {
        case 'n': y++; break;
        case 'w': x--; break;
        case 's': y--; break;
        case 'e': x++; break;
        default:
            cout << "\nWrong character inserted, Try again !!" << endl;
        }

        // Conditional operator with logical operators:
        int result = (x == 7 && y == 11) ? 1 : 0;

        if (result == 1) {
            cout << "\nYou found the treasure !!" << endl;
            return 0;
        }
    }

    cout << "\nExiting.\n";
    return 0;
}
