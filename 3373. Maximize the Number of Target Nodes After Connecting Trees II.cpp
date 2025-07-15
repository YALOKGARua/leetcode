#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        int n = edges1.size() + 1, m = edges2.size() + 1;
        vector<vector<int>> g1(n), g2(m);
        for (auto& e : edges1) {
            g1[e[0]].push_back(e[1]);
            g1[e[1]].push_back(e[0]);
        }
        for (auto& e : edges2) {
            g2[e[0]].push_back(e[1]);
            g2[e[1]].push_back(e[0]);
        }
        vector<int> depth1(n, -1), cnt1(2, 0);
        queue<int> q;
        q.push(0);
        depth1[0] = 0;
        cnt1[0]++;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : g1[u]) {
                if (depth1[v] == -1) {
                    depth1[v] = depth1[u] + 1;
                    cnt1[depth1[v] % 2]++;
                    q.push(v);
                }
            }
        }
        vector<int> depth2(m, -1), cnt2(2, 0);
        q.push(0);
        depth2[0] = 0;
        cnt2[0]++;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : g2[u]) {
                if (depth2[v] == -1) {
                    depth2[v] = depth2[u] + 1;
                    cnt2[depth2[v] % 2]++;
                    q.push(v);
                }
            }
        }
        vector<int> ans(n);
        for (int i = 0; i < n; ++i) {
            int parity = depth1[i] % 2;
            int res1 = cnt1[parity] + cnt2[1 - parity];
            int res2 = cnt1[parity] + cnt2[parity];
            ans[i] = max(res1, res2);
        }
        return ans;
    }
};
