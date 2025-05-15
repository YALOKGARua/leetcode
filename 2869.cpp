#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        unordered_set<int> collected;
        int operations = 0;
        
        for (int i = nums.size() - 1; i >= 0; --i) {
            operations++;
            if (nums[i] <= k) {
                collected.insert(nums[i]);
            }
            if (collected.size() == k) {
                return operations;
            }
        }
        
        return operations;
    }
}; 