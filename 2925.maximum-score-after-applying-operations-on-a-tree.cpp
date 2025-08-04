#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    long long maximumScoreAfterOperations(vector<vector<int>>& edges, vector<int>& values) {
        int n = values.size();
        vector<vector<int>> adj(n);
        
        for (auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        
        vector<vector<long long>> dp(n, vector<long long>(2, -1));
        
        auto result = dfs(0, -1, adj, values, dp);
        return result.first;
    }
    
private:
    pair<long long, long long> dfs(int node, int parent, vector<vector<int>>& adj, 
                                   vector<int>& values, vector<vector<long long>>& dp) {
        vector<int> children;
        for (int child : adj[node]) {
            if (child != parent) {
                children.push_back(child);
            }
        }
        
        if (children.empty()) {
            return {values[node], 0};
        }
        
        long long takeCurrent = values[node];
        long long notTakeCurrent = 0;
        bool hasValidNotTake = false;
        
        for (int child : children) {
            auto childResult = dfs(child, node, adj, values, dp);
            takeCurrent += childResult.first;
            
            if (childResult.second != -1) {
                notTakeCurrent += childResult.second;
                hasValidNotTake = true;
            } else {
                notTakeCurrent += childResult.first;
            }
        }
        
        if (hasValidNotTake) {
            return {takeCurrent, notTakeCurrent};
        } else {
            return {takeCurrent, -1};
        }
    }
}; 