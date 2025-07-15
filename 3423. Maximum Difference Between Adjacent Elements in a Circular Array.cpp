#include <vector>
#include <cstdlib>
using namespace std;

class Solution {
public:
    int maxAdjacentDistance(vector<int>& nums) {
        int n = nums.size(), res = 0;
        for (int i = 0; i < n; ++i) {
            int diff = abs(nums[i] - nums[(i + 1) % n]);
            if (diff > res) res = diff;
        }
        return res;
    }
};
