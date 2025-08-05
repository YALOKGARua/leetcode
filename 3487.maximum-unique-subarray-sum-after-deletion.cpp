#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
        int maxSum(vector<int>& nums) {
        unordered_map<int, int> freq;
        int left = 0, sum = 0, maxSum = nums[0];
        for (int right = 0; right < nums.size(); ++right) {
            freq[nums[right]]++;
            sum += nums[right];
            while (freq[nums[right]] > 1) {
                freq[nums[left]]--;
                sum -= nums[left];
                left++;
            }
            maxSum = max(maxSum, sum);
        }
        return maxSum;
    }
}; 