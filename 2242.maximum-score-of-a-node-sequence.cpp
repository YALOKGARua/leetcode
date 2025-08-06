class Solution {
public:
    int maximumScore(vector<int>& scores, vector<vector<int>>& edges) {
        int n = scores.size();
        vector<vector<int>> graph(n);
        
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        
        long long maxScore = -1;
        
        for (int i = 0; i < n; i++) {
            for (int j : graph[i]) {
                if (j == i) continue;
                
                for (int k : graph[j]) {
                    if (k == i || k == j) continue;
                    
                    for (int l : graph[k]) {
                        if (l == i || l == j || l == k) continue;
                        
                        long long currentScore = (long long)scores[i] + scores[j] + scores[k] + scores[l];
                        maxScore = max(maxScore, currentScore);
                    }
                }
            }
        }
        
        return maxScore;
    }
}; 