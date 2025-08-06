class Solution {
public:
    vector<int> longestSpecialPath(vector<vector<int>>& edges, vector<int>& nums) {
        int n = nums.size();
        vector<vector<pair<int, int>>> adj(n);
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1], len = edge[2];
            adj[u].push_back({v, len});
            adj[v].push_back({u, len});
        }
        vector<int> result = {0, 0};
        function<void(int, int, long long, int, unordered_map<int, int>, int)> dfs = [&](int node, int parent, long long pathLen, int pathNodes, unordered_map<int, int> count, int duplicates) {
            count[nums[node]]++;
            if (count[nums[node]] == 2) duplicates++;
            pathNodes++;
            if (duplicates <= 1) {
                if (pathLen > result[0]) {
                    result[0] = pathLen;
                    result[1] = pathNodes;
                } else if (pathLen == result[0]) {
                    result[1] = min(result[1], pathNodes);
                }
            }
            for (auto& [child, len] : adj[node]) {
                if (child != parent) {
                    dfs(child, node, pathLen + len, pathNodes, count, duplicates);
                }
            }
            count[nums[node]]--;
            if (count[nums[node]] == 1) duplicates--;
        };
        for (int i = 0; i < n; ++i) {
            unordered_map<int, int> count;
            dfs(i, -1, 0, 0, count, 0);
        }
        return result;
    }
}; 