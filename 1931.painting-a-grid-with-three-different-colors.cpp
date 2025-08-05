class Solution {
private:
    const int MOD = 1e9 + 7;
    
    bool isValid(int mask, int m) {
        for (int i = 0; i < m; i++) {
            int color = (mask >> (2 * i)) & 3;
            if (color >= 3) return false;
        }
        for (int i = 1; i < m; i++) {
            int curr = (mask >> (2 * i)) & 3;
            int prev = (mask >> (2 * (i - 1))) & 3;
            if (curr == prev) return false;
        }
        return true;
    }
    
    bool isCompatible(int mask1, int mask2, int m) {
        for (int i = 0; i < m; i++) {
            int color1 = (mask1 >> (2 * i)) & 3;
            int color2 = (mask2 >> (2 * i)) & 3;
            if (color1 == color2) return false;
        }
        return true;
    }
    
public:
    int colorTheGrid(int m, int n) {
        vector<int> validStates;
        
        for (int mask = 0; mask < (1 << (2 * m)); mask++) {
            if (isValid(mask, m)) {
                validStates.push_back(mask);
            }
        }
        
        int stateCount = validStates.size();
        vector<vector<int>> dp(n, vector<int>(stateCount, 0));
        
        for (int i = 0; i < stateCount; i++) {
            dp[0][i] = 1;
        }
        
        for (int col = 1; col < n; col++) {
            for (int currState = 0; currState < stateCount; currState++) {
                for (int prevState = 0; prevState < stateCount; prevState++) {
                    if (isCompatible(validStates[currState], validStates[prevState], m)) {
                        dp[col][currState] = (dp[col][currState] + dp[col - 1][prevState]) % MOD;
                    }
                }
            }
        }
        
        int result = 0;
        for (int i = 0; i < stateCount; i++) {
            result = (result + dp[n - 1][i]) % MOD;
        }
        
        return result;
    }
}; 