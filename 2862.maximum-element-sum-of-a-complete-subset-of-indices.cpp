class Solution {
private:
    int getSquareFreePart(int x) {
        int result = 1;
        
        for (int i = 2; i * i <= x; i++) {
            int count = 0;
            while (x % i == 0) {
                x /= i;
                count++;
            }
            if (count % 2 == 1) {
                result *= i;
            }
        }
        
        if (x > 1) {
            result *= x;
        }
        
        return result;
    }
    
public:
    long long maximumSum(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, long long> groupSums;
        
        for (int i = 1; i <= n; i++) {
            int squareFree = getSquareFreePart(i);
            groupSums[squareFree] += nums[i - 1];
        }
        
        long long maxSum = 0;
        for (auto& [group, sum] : groupSums) {
            maxSum = max(maxSum, sum);
        }
        
        return maxSum;
    }
}; 