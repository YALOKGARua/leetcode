#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    long long largestPerimeter(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        long long sum = 0;
        for (int x : nums) sum += x;
        for (int i = nums.size() - 1; i >= 2; --i) {
            sum -= nums[i];
            if (sum > nums[i]) return sum + nums[i];
        }
        return -1;
    }
}; 