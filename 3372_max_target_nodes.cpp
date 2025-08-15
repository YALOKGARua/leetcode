#include <vector>
#include <queue>

using std::vector;

class Solution {
public:
	vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2, int k) {
		int n = (int)edges1.size() + 1;
		int m = (int)edges2.size() + 1;
		vector<vector<int>> g1(n), g2(m);
		for (auto& e : edges1) {
			int a = e[0], b = e[1];
			g1[a].push_back(b);
			g1[b].push_back(a);
		}
		for (auto& e : edges2) {
			int u = e[0], v = e[1];
			g2[u].push_back(v);
			g2[v].push_back(u);
		}
		auto countWithin = [&](const vector<vector<int>>& g, int start, int limit) {
			if (limit < 0) return 0;
			int sz = (int)g.size();
			std::queue<int> q;
			vector<int> dist(sz, -1);
			dist[start] = 0;
			q.push(start);
			int cnt = 0;
			while (!q.empty()) {
				int x = q.front();
				q.pop();
				++cnt;
				if (dist[x] == limit) continue;
				for (int y : g[x]) if (dist[y] == -1) {
					dist[y] = dist[x] + 1;
					q.push(y);
				}
			}
			return cnt;
		};
		vector<int> ans(n);
		for (int i = 0; i < n; ++i) ans[i] = countWithin(g1, i, k);
		int kd = k - 1;
		int best = 0;
		for (int p = 0; p < m; ++p) {
			int c = countWithin(g2, p, kd);
			if (c > best) best = c;
		}
		for (int i = 0; i < n; ++i) ans[i] += best;
		return ans;
	}
};