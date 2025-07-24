#include <vector>
#include <unordered_set>
#include <algorithm>
using std::vector;
using std::unordered_set;

class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        unordered_set<int> seen;
        int res = 0, curr = 0, l = 0;
        for (int r = 0; r < n; ++r) {
            while (seen.count(nums[r])) {
                seen.erase(nums[l]);
                curr -= nums[l];
                ++l;
            }
            seen.insert(nums[r]);
            curr += nums[r];
            res = std::max(res, curr);
        }
        return res;
    }
}; 