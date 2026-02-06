#include <iostream>
using namespace std;

int calcSum(int a, int b, int c) {
    
    // Your code here
    int sum = 0;
    sum = a + b + c;
    return  sum;


}

int main() {
    cout << "Enter the time you want to calculate the sum: " << endl;
    int T, a, b, c;
    cin >> T;

    cout << "enter the numbers a, b, c:" << endl;
    cin >> a;
    cin >> b;
    cin >> c;
    for (int i = 0; i < T; ++i) {
        
        int res = calcSum(a, b, c);
        a += 3;
        b += 3;
        c += 3;
        cout << res << endl;
    }

    
}