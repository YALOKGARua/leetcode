#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    long long maximumValueSum(vector<int>& nums, int k, vector<vector<int>>& edges) {
        int n = nums.size();
        vector<long long> diff(n);
        long long sum = 0;
        
        for (int i = 0; i < n; i++) {
            sum += nums[i];
            diff[i] = (nums[i] ^ k) - nums[i];
        }
        
        sort(diff.begin(), diff.end(), greater<long long>());
        
        for (int i = 0; i < n - 1; i += 2) {
            if (diff[i] + diff[i + 1] > 0) {
                sum += diff[i] + diff[i + 1];
            } else {
                break;
            }
        }
        
        return sum;
    }
}; 