#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int numSubseq(vector<int>& nums, int target) {
        const int MOD = 1e9 + 7;
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<int> pow2(n + 1, 1);
        for (int i = 1; i <= n; ++i) pow2[i] = (pow2[i - 1] * 2) % MOD;
        int res = 0, l = 0, r = n - 1;
        while (l <= r) {
            if (nums[l] + nums[r] <= target) {
                res = (res + pow2[r - l]) % MOD;
                ++l;
            } else {
                --r;
            }
        }
        return res;
    }
};
