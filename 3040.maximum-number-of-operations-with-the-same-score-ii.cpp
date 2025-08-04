class Solution {
public:
    int maxOperations(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) return 0;
        
        vector<int> possibleScores;
        if (n >= 2) {
            possibleScores.push_back(nums[0] + nums[1]);
            possibleScores.push_back(nums[n-2] + nums[n-1]);
        }
        if (n >= 2) {
            possibleScores.push_back(nums[0] + nums[n-1]);
        }
        
        int maxOps = 0;
        for (int targetScore : possibleScores) {
            maxOps = max(maxOps, solve(nums, targetScore));
        }
        
        return maxOps;
    }
    
private:
    int solve(vector<int>& nums, int targetScore) {
        int n = nums.size();
        vector<vector<int>> memo(n, vector<int>(n, -1));
        return dp(nums, 0, n-1, targetScore, memo);
    }
    
    int dp(vector<int>& nums, int left, int right, int targetScore, vector<vector<int>>& memo) {
        if (left >= right) return 0;
        
        if (memo[left][right] != -1) {
            return memo[left][right];
        }
        
        int maxOps = 0;
        
        if (left + 1 <= right && nums[left] + nums[left + 1] == targetScore) {
            maxOps = max(maxOps, 1 + dp(nums, left + 2, right, targetScore, memo));
        }
        
        if (right - 1 >= left && nums[right - 1] + nums[right] == targetScore) {
            maxOps = max(maxOps, 1 + dp(nums, left, right - 2, targetScore, memo));
        }
        
        if (left < right && nums[left] + nums[right] == targetScore) {
            maxOps = max(maxOps, 1 + dp(nums, left + 1, right - 1, targetScore, memo));
        }
        
        memo[left][right] = maxOps;
        return maxOps;
    }
}; 