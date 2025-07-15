#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxDistance(string s, int k) {
        int n = s.size();
        vector<pair<int, int>> pos(n + 1, {0, 0});
        for (int i = 0; i < n; ++i) {
            pos[i + 1] = pos[i];
            if (s[i] == 'N') pos[i + 1].second++;
            if (s[i] == 'S') pos[i + 1].second--;
            if (s[i] == 'E') pos[i + 1].first++;
            if (s[i] == 'W') pos[i + 1].first--;
        }
        int res = 0;
        for (int i = 0; i <= n; ++i) {
            int x = pos[i].first, y = pos[i].second;
            int remain = k;
            int dx = max(abs(x + remain), abs(x - remain));
            int dy = max(abs(y + remain), abs(y - remain));
            res = max(res, dx + dy);
        }
        return res;
    }
};
