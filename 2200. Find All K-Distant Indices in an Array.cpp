#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    vector<int> findKDistantIndices(vector<int>& nums, int key, int k) {
        unordered_set<int> res;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            if (nums[i] == key) {
                for (int j = max(0, i - k); j <= min(n - 1, i + k); ++j) {
                    res.insert(j);
                }
            }
        }
        vector<int> ans(res.begin(), res.end());
        sort(ans.begin(), ans.end());
        return ans;
    }
};