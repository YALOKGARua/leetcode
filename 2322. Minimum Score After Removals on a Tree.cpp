#include <vector>
#include <algorithm>
#include <climits>
#include <functional>

using std::vector;

class Solution {
public:
    int minimumScore(vector<int>& nums, vector<vector<int>>& edges) {
        int n = nums.size();
        vector<vector<int>> g(n);
        for (const auto& e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        vector<int> subtreeXor(n);
        vector<int> in(n), out(n);
        int timer = 0;
        std::function<void(int, int)> dfs = [&](int u, int p) {
            in[u] = timer++;
            subtreeXor[u] = nums[u];
            for (int v : g[u]) {
                if (v == p) continue;
                dfs(v, u);
                subtreeXor[u] ^= subtreeXor[v];
            }
            out[u] = timer++;
        };
        dfs(0, -1);
        auto isAncestor = [&](int u, int v) {
            return in[u] <= in[v] && out[v] <= out[u];
        };
        int res = INT_MAX;
        for (int i = 0; i < edges.size(); ++i) {
            int a = edges[i][0], b = edges[i][1];
            if (in[a] > in[b]) std::swap(a, b); // a is parent of b
            for (int j = i + 1; j < edges.size(); ++j) {
                int c = edges[j][0], d = edges[j][1];
                if (in[c] > in[d]) std::swap(c, d); // c is parent of d
                int x, y, z;
                if (isAncestor(b, d)) {
                    x = subtreeXor[d];
                    y = subtreeXor[b] ^ subtreeXor[d];
                    z = subtreeXor[0] ^ subtreeXor[b];
                } else if (isAncestor(d, b)) {
                    x = subtreeXor[b];
                    y = subtreeXor[d] ^ subtreeXor[b];
                    z = subtreeXor[0] ^ subtreeXor[d];
                } else {
                    x = subtreeXor[b];
                    y = subtreeXor[d];
                    z = subtreeXor[0] ^ subtreeXor[b] ^ subtreeXor[d];
                }
                int mx = std::max({x, y, z});
                int mn = std::min({x, y, z});
                res = std::min(res, mx - mn);
            }
        }
        return res;
    }
}; 