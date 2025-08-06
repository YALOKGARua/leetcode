class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> graph(n);
        for (auto& inv : invocations) {
            graph[inv[0]].push_back(inv[1]);
        }
        vector<bool> suspicious(n, false);
        function<void(int)> dfs = [&](int node) {
            if (suspicious[node]) return;
            suspicious[node] = true;
            for (int neighbor : graph[node]) {
                dfs(neighbor);
            }
        };
        dfs(k);
        vector<bool> canRemove(n, true);
        for (int i = 0; i < n; ++i) {
            if (!suspicious[i]) {
                for (int neighbor : graph[i]) {
                    canRemove[neighbor] = false;
                }
            }
        }
        vector<int> result;
        for (int i = 0; i < n; ++i) {
            if (!suspicious[i] || !canRemove[i]) {
                result.push_back(i);
            }
        }
        return result;
    }
}; 