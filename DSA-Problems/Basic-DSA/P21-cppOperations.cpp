
#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    vector<int> cppOperators(int A, int B) {
        // code here

        vector<int> cppOper;

        cppOper.push_back(A + B);
        cppOper.push_back(A * B);
        if (B > A) {
            cppOper.push_back(B - A);
            cppOper.push_back(B / A);
        }
        else {
            cppOper.push_back(A - B);
            cppOper.push_back(A / B);
        }


        return cppOper;
    }
};

int main() {

    Solution s;
    vector<int> result = s.cppOperators(12, 18);

    for (int r : result) {
        cout << r << " ";
    }
}