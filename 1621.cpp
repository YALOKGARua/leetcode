#include <vector>
using namespace std;

class Solution {
public:
    int numberOfSets(int n, int k) {
        const int MOD = 1e9 + 7;
        vector<vector<vector<long long>>> dp(n, vector<vector<long long>>(k + 1, vector<long long>(2, 0)));
        
        dp[0][0][0] = 1;
        
        for(int i = 1; i < n; i++) {
            for(int j = 0; j <= k; j++) {
                dp[i][j][0] = (dp[i-1][j][0] + dp[i-1][j][1]) % MOD;
                
                if(j > 0) {
                    dp[i][j][1] = (dp[i-1][j][1] + dp[i-1][j-1][0] + dp[i-1][j-1][1]) % MOD;
                }
            }
        }
        
        return (dp[n-1][k][0] + dp[n-1][k][1]) % MOD;
    }
};