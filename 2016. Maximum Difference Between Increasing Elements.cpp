#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumDifference(vector<int>& nums) {
        if (nums.empty()) return -1;
        long long minVal = nums[0];
        long long best = -1;
        for (size_t i = 1; i < nums.size(); ++i) {
            if (nums[i] > minVal) {
                long long diff = (long long)nums[i] - minVal;
                if (diff > best) best = diff;
            } else {
                if (nums[i] < minVal) minVal = nums[i];
            }
        }
        return (int)best;
    }
};