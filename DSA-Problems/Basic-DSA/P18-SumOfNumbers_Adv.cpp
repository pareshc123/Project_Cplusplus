/*

    C++ Functions (Sum of numbers) | Set 1
    
    Given three numbers A, B, C you have to write a function named calcSum() which takes these 3 numbers as arguments and 
    returns their sum.

    Input:
        The input line contains T, which denotes the number of testcases. Then T test cases follow. 
        Each test case consists of a single line which contains three space separated integers A, B, and C.

    Output:
        Corresponding to each testcase, output sum of A, B and C in a new line.

    User Task:
        Since this is a functional problem you don't have to worry about input, you just have to complete the function calcSum().

    Constraints:
        1 <= T <= 105
        1 <= A <= 102
        1 <= B <= 102
        1 <= C <= 102

    Example:
        Input:
        3
        1 2 3
        5 6 7
        2 5 3

        Output:
        6
        18
        10

        Explanation:
        Testcase 1: Sum of the given 1,2 and 3 is 6.

*/

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