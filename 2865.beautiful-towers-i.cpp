class Solution {
public:
    long long maximumSumOfHeights(vector<int>& heights) {
        int n = heights.size();
        long long maxSum = 0;
        
        for (int peak = 0; peak < n; peak++) {
            long long currentSum = 0;
            vector<int> mountain(n);
            
            mountain[peak] = heights[peak];
            currentSum += mountain[peak];
            
            for (int i = peak - 1; i >= 0; i--) {
                mountain[i] = min(heights[i], mountain[i + 1]);
                currentSum += mountain[i];
            }
            
            for (int i = peak + 1; i < n; i++) {
                mountain[i] = min(heights[i], mountain[i - 1]);
                currentSum += mountain[i];
            }
            
            maxSum = max(maxSum, currentSum);
        }
        
        return maxSum;
    }
}; 