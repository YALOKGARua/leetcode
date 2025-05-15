#include <vector>
using namespace std;

class Solution {
    vector<vector<pair<int,int>>> adj;
    vector<int> ans;
    
    int dfs(int u, int p) {
        int res = 0;
        for (auto [v, isReverse] : adj[u]) {
            if (v != p) {
                res += isReverse + dfs(v, u);
            }
        }
        return res;
    }
    
    void reroot(int u, int p, int curr) {
        ans[u] = curr;
        for (auto [v, isReverse] : adj[u]) {
            if (v != p) {
                reroot(v, u, curr - isReverse + (1 - isReverse));
            }
        }
    }
    
public:
    vector<int> minEdgeReversals(int n, vector<vector<int>>& edges) {
        adj.resize(n);
        ans.resize(n);
        
        for (auto& e : edges) {
            adj[e[0]].push_back({e[1], 0});
            adj[e[1]].push_back({e[0], 1});
        }
        
        int root_ans = dfs(0, -1);
        reroot(0, -1, root_ans);
        
        return ans;
    }
}; 