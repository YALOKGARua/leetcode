#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumLength(vector<int>& nums) {
        int evenCount = 0;
        int oddCount = 0;
        int parityRunCount = 0;
        int previousParity = -1;
        for (int value : nums) {
            int parity = value & 1;
            if (parity == 0) {
                ++evenCount;
            } else {
                ++oddCount;
            }
            if (parity != previousParity) {
                ++parityRunCount;
                previousParity = parity;
            }
        }
        return max(parityRunCount, max(evenCount, oddCount));
    }
};