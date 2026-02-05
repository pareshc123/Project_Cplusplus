#include <iostream>
using namespace std;


void bruteForceCode(int n) {

    for (int row = 0; row < n; ++row) {
        for (int column = 0; column < n; ++column) {
            if (row == 0 || row == n - 1 || column == 0 || column == n - 1) {
                cout << "*";
            }
            else {
                cout << " ";

            }
        }
        cout << endl;
    }
}


void optimizeCode(int n) {

}


int main() {

    // code here
    int n = 5;
    
    bruteForceCode(n);
    optimizeCode(n);

    return 0;
}