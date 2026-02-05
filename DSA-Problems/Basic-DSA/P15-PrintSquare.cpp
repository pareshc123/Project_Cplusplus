#include <iostream>
using namespace std;


void bruteForceCode(int n) {

    for (int row = 0; row < n; ++row) {
        for (int column = 0; column < n; ++column) {
            if (row == 0 || row == n - 1 || column == 0 || column == n - 1) {
                cout << "* ";
            }
            else {
                cout << "  ";

            }
        }
        cout << endl;
    }
}


void optimizeCode(int n) {
    
    string res = "";

    for (int row = 0; row < n; ++row) {
        
        if (row == 0 || row == n - 1) {
            
            for (int column = 0; column < n; ++column) {           // first and last rows
                res += "* ";
            }
        } else {
            res += "* ";
            for (int column = 0; column < n - 2; ++column) {       // middle rows:
                res += "  ";
            }
            res += "* ";
        }
        res += "\n";

    }

    cout << res;
}


int main() {

    // code here
    int n = 2;
    
    bruteForceCode(n);
    optimizeCode(n);

    return 0;
}