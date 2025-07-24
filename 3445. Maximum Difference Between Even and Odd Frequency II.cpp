#include <string>
#include <vector>
#include <algorithm>
#include <climits>
#include <deque>
using std::string;
using std::vector;
using std::max;
using std::deque;

class Solution {
public:
    int maxDifference(string s, int k) {
        int n = s.size();
        int res = INT_MIN;
        for (char a = '0'; a <= '4'; ++a) {
            for (char b = '0'; b <= '4'; ++b) {
                if (a == b) continue;
                vector<int> cntA(n + 1, 0), cntB(n + 1, 0), diff(n + 1, 0);
                for (int i = 0; i < n; ++i) {
                    cntA[i + 1] = cntA[i] + (s[i] == a);
                    cntB[i + 1] = cntB[i] + (s[i] == b);
                    diff[i + 1] = cntA[i + 1] - cntB[i + 1];
                }
                deque<std::pair<int, int>> dq[2][2][2];
                for (int i = 0; i <= n; ++i) {
                    int pa = cntA[i] % 2;
                    int pb = cntB[i] % 2;
                    int hasB = cntB[i] > 0 ? 1 : 0;
                    if (!dq[pa][pb][hasB].empty()) {
                        while (!dq[pa][pb][hasB].empty() && dq[pa][pb][hasB].front().first < i - k + 1) dq[pa][pb][hasB].pop_front();
                        if (!dq[pa][pb][hasB].empty()) {
                            int j = dq[pa][pb][hasB].front().first;
                            int subA = cntA[i] - cntA[j];
                            int subB = cntB[i] - cntB[j];
                            if (subA % 2 == 1 && subB > 0 && subB % 2 == 0) {
                                res = max(res, diff[i] - dq[pa][pb][hasB].front().second);
                            }
                        }
                    }
                    if (i >= k) {
                        int pa0 = cntA[i - k] % 2;
                        int pb0 = cntB[i - k] % 2;
                        int hasB0 = cntB[i - k] > 0 ? 1 : 0;
                        auto& q = dq[pa0][pb0][hasB0];
                        while (!q.empty() && q.back().second >= diff[i - k]) q.pop_back();
                        q.emplace_back(i - k, diff[i - k]);
                    }
                }
            }
        }
        return res == INT_MIN ? -1 : res;
    }
};