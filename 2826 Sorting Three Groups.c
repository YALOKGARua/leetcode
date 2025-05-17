int min(int a, int b) {
    return a < b ? a : b;
}

int minimumOperations(int* nums, int numsSize) {
    int dp[3] = {0, 0, 0};
    
    for (int i = 0; i < numsSize; i++) {
        int ndp[3] = {0, 0, 0};
        
        ndp[0] = dp[0] + (nums[i] != 1);
        ndp[1] = min(dp[0], dp[1]) + (nums[i] != 2);
        ndp[2] = min(min(dp[0], dp[1]), dp[2]) + (nums[i] != 3);
        
        dp[0] = ndp[0];
        dp[1] = ndp[1];
        dp[2] = ndp[2];
    }
    
    return min(min(dp[0], dp[1]), dp[2]);
} 