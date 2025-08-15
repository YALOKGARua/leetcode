#include <vector>
#include <queue>

using std::vector;

class Solution {
public:
	vector<int> countSubgraphsForEachDiameter(int n, vector<vector<int>>& edges) {
		vector<vector<int>> g(n);
		for (auto& e : edges) {
			int u = e[0] - 1, v = e[1] - 1;
			g[u].push_back(v);
			g[v].push_back(u);
		}
		vector<vector<int>> dist(n, vector<int>(n, -1));
		for (int s = 0; s < n; ++s) {
			std::queue<int> q;
			dist[s][s] = 0;
			q.push(s);
			while (!q.empty()) {
				int u = q.front();
				q.pop();
				for (int v : g[u]) if (dist[s][v] == -1) {
					dist[s][v] = dist[s][u] + 1;
					q.push(v);
				}
			}
		}
		vector<int> ans(n - 1, 0);
		int m = (int)edges.size();
		for (int mask = 1; mask < (1 << n); ++mask) {
			int c = __builtin_popcount((unsigned int)mask);
			if (c < 2) continue;
			int edgeCount = 0;
			for (int i = 0; i < m; ++i) {
				int u = edges[i][0] - 1, v = edges[i][1] - 1;
				if ((mask & (1 << u)) && (mask & (1 << v))) ++edgeCount;
			}
			if (edgeCount != c - 1) continue;
			int d = 0;
			for (int u = 0; u < n; ++u) if (mask & (1 << u)) {
				for (int v = u + 1; v < n; ++v) if (mask & (1 << v)) {
					if (dist[u][v] > d) d = dist[u][v];
				}
			}
			if (d >= 1) ++ans[d - 1];
		}
		return ans;
	}
};