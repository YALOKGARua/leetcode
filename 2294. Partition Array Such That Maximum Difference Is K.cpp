#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int partitionArray(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int res = 1, start = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] - start > k) {
                res++;
                start = nums[i];
            }
        }
        return res;
    }
};
