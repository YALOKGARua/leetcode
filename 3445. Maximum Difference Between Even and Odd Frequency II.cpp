#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxDistance(string s, int k) {
        int n = s.size();
        vector<int> dx = {0, 0, 1, -1};
        vector<int> dy = {1, -1, 0, 0};
        string dirs = "NSEW";
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, INT_MIN));
        dp[0][0] = 0;
        int x = 0, y = 0;
        for (int i = 0; i < n; ++i) {
            vector<vector<int>> ndp(n + 1, vector<int>(k + 1, INT_MIN));
            for (int j = 0; j <= k; ++j) {
                if (dp[i][j] == INT_MIN) continue;
                int cx = x, cy = y;
                if (s[i] == 'N') cy++;
                if (s[i] == 'S') cy--;
                if (s[i] == 'E') cx++;
                if (s[i] == 'W') cx--;
                ndp[i + 1][j] = max(ndp[i + 1][j], abs(cx) + abs(cy));
                if (j < k) {
                    for (int d = 0; d < 4; ++d) {
                        int nx = x + dx[d], ny = y + dy[d];
                        ndp[i + 1][j + 1] = max(ndp[i + 1][j + 1], abs(nx) + abs(ny));
                    }
                }
            }
            x = 0, y = 0;
            for (int t = 0; t <= i + 1; ++t) {
                if (s[t] == 'N') y++;
                if (s[t] == 'S') y--;
                if (s[t] == 'E') x++;
                if (s[t] == 'W') x--;
            }
            dp = ndp;
        }
        int res = 0;
        for (int j = 0; j <= k; ++j) res = max(res, dp[n][j]);
        return res;
    }
};