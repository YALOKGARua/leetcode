#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxValue(vector<vector<int>>& events, int k) {
        int n = events.size();
        sort(events.begin(), events.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });
        vector<int> ends;
        for (const auto& e : events) ends.push_back(e[1]);
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
        for (int i = 1; i <= n; ++i) {
            int start = events[i-1][0], end = events[i-1][1], val = events[i-1][2];
            int prev = lower_bound(ends.begin(), ends.end(), start) - ends.begin();
            prev--;
            for (int j = 1; j <= k; ++j) {
                dp[i][j] = max(dp[i][j], dp[i-1][j]);
                if (prev >= 0)
                    dp[i][j] = max(dp[i][j], dp[prev+1][j-1] + val);
                else
                    dp[i][j] = max(dp[i][j], val);
            }
        }
        return dp[n][k];
    }
};
