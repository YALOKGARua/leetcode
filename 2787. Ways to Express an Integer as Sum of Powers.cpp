class Solution {
public:
    int numberOfWays(int n, int x) {
        const int MOD = 1000000007;
        long long i = 1;
        std::vector<int> powers;
        while (true) {
            long long p = 1;
            for (int k = 0; k < x; ++k) {
                p *= i;
                if (p > n) break;
            }
            if (p > n) break;
            powers.push_back((int)p);
            ++i;
        }
        std::vector<int> dp(n + 1);
        dp[0] = 1;
        for (int p : powers) {
            for (int s = n; s >= p; --s) {
                dp[s] += dp[s - p];
                if (dp[s] >= MOD) dp[s] -= MOD;
            }
        }
        return dp[n];
    }
};