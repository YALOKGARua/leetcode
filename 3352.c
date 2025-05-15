#include <string.h>

#define MOD 1000000007

int popcount(int x) {
    int res = 0;
    while (x) {
        res += x & 1;
        x >>= 1;
    }
    return res;
}

int reduce_steps(int x) {
    int steps = 0;
    while (x > 1) {
        x = popcount(x);
        steps++;
    }
    return steps;
}

int dp[805][805][2];

int solve(char* s, int k) {
    int n = strlen(s);
    memset(dp, 0, sizeof(dp));
    dp[0][0][1] = 1;
    for (int i = 0; i < n; i++) {
        for (int cnt = 0; cnt <= i; cnt++) {
            for (int tight = 0; tight < 2; tight++) {
                int limit = tight ? (s[i] - '0') : 1;
                for (int d = 0; d <= limit; d++) {
                    int ntight = (tight && d == limit);
                    dp[i + 1][cnt + d][ntight] = (dp[i + 1][cnt + d][ntight] + dp[i][cnt][tight]) % MOD;
                }
            }
        }
    }
    int ans = 0;
    for (int cnt = 1; cnt <= n; cnt++) {
        if (k == 0 && cnt != 1) continue;
        if (k == 1) {
            if (cnt == 1) {
                ans = (ans + dp[n][cnt][0]) % MOD;
            }
        } else if (k > 1 && reduce_steps(cnt) <= k - 1) {
            ans = (ans + dp[n][cnt][0]) % MOD;
        }
    }
    if (k == 0) return 0;
    return ans;
}

int countKReducibleNumbers(char* s, int k) {
    if (strcmp(s, "1") == 0) return 0;
    return solve(s, k);
} 