class Solution {
public:
    int stringCount(int n) {
        const int MOD = 1e9 + 7;
        if (n < 4) return 0;
        vector<vector<vector<vector<long long>>>> dp(n + 1, vector<vector<vector<long long>>>(2, vector<vector<long long>>(2, vector<long long>(3, 0))));
        dp[0][0][0][0] = 1;
        for (int i = 0; i < n; ++i) {
            for (int l = 0; l <= 1; ++l) {
                for (int t = 0; t <= 1; ++t) {
                    for (int e = 0; e <= 2; ++e) {
                        if (dp[i][l][t][e] == 0) continue;
                        for (int c = 0; c < 26; ++c) {
                            int nl = l, nt = t, ne = e;
                            if (c == 'l' - 'a') nl = min(1, l + 1);
                            else if (c == 't' - 'a') nt = min(1, t + 1);
                            else if (c == 'e' - 'a') ne = min(2, e + 1);
                            dp[i + 1][nl][nt][ne] = (dp[i + 1][nl][nt][ne] + dp[i][l][t][e]) % MOD;
                        }
                    }
                }
            }
        }
        return (int)dp[n][1][1][2];
    }
}; 