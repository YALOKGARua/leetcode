#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minMaxDifference(int num) {
        string originalString = to_string(num);
        string maxString = originalString;
        string minString = originalString;

        char digitToMaximize = 0;
        bool foundDigitToMaximize = false;
        for (char c : originalString) {
            if (c != '9') {
                digitToMaximize = c;
                foundDigitToMaximize = true;
                break;
            }
        }
        if (foundDigitToMaximize) {
            for (char& c : maxString) {
                if (c == digitToMaximize) c = '9';
            }
        }

        char digitToMinimize = 0;
        bool foundDigitToMinimize = false;
        for (char c : originalString) {
            if (c != '0') {
                digitToMinimize = c;
                foundDigitToMinimize = true;
                break;
            }
        }
        if (foundDigitToMinimize) {
            for (char& c : minString) {
                if (c == digitToMinimize) c = '0';
            }
        }

        long long maxValue = stoll(maxString);
        long long minValue = stoll(minString);
        return static_cast<int>(maxValue - minValue);
    }
};