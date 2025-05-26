#include <vector>
using namespace std;

class Solution {
public:
    bool isZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<int> diff(n + 1, 0);
        
        for (const auto& query : queries) {
            int l = query[0], r = query[1];
            diff[l]++;
            if (r + 1 < n) {
                diff[r + 1]--;
            }
        }
        
        int curr = 0;
        for (int i = 0; i < n; i++) {
            curr += diff[i];
            if (curr < nums[i]) {
                return false;
            }
        }
        
        return true;
    }
}; 