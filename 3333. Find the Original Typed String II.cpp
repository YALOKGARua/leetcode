#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int possibleStringCount(string word, int k) {
        const int MOD = 1e9 + 7;
        int n = word.size();
        vector<int> groupLens;
        for (int i = 0; i < n;) {
            int j = i;
            while (j < n && word[j] == word[i]) ++j;
            groupLens.push_back(j - i);
            i = j;
        }
        vector<int> dp(n + 2, 0), ndp(n + 2, 0);
        dp[0] = 1;
        for (int len : groupLens) {
            fill(ndp.begin(), ndp.end(), 0);
            for (int i = 0; i <= n; ++i) {
                if (dp[i] == 0) continue;
                int l = i + 1, r = i + len;
                if (l <= n) {
                    ndp[l] = (ndp[l] + dp[i]) % MOD;
                    if (r + 1 <= n) ndp[r + 1] = (ndp[r + 1] - dp[i] + MOD) % MOD;
                }
            }
            int sum = 0;
            for (int i = 0; i <= n; ++i) {
                sum = (sum + ndp[i]) % MOD;
                dp[i] = sum;
            }
        }
        int total = 0;
        for (int i = k; i <= n; ++i) total = (total + dp[i]) % MOD;
        return total;
    }
};