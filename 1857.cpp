#include <string>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        int n = colors.length();
        vector<vector<int>> graph(n);
        vector<int> inDegree(n, 0);
        
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            inDegree[edge[1]]++;
        }
        
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }
        
        vector<vector<int>> dp(n, vector<int>(26, 0));
        int visited = 0;
        int result = 0;
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            visited++;
            
            dp[node][colors[node] - 'a']++;
            result = max(result, dp[node][colors[node] - 'a']);
            
            for (int neighbor : graph[node]) {
                for (int i = 0; i < 26; i++) {
                    dp[neighbor][i] = max(dp[neighbor][i], dp[node][i]);
                }
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }
        
        return visited == n ? result : -1;
    }
}; 