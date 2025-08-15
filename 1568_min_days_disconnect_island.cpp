#include <vector>
#include <queue>

using std::vector;

class Solution {
public:
	int minDays(vector<vector<int>>& grid) {
		int m = (int)grid.size();
		int n = (int)grid[0].size();
		auto countIslands = [&](vector<vector<int>>& g) {
			vector<vector<int>> vis(m, vector<int>(n, 0));
			int cnt = 0;
			for (int i = 0; i < m; ++i) {
				for (int j = 0; j < n; ++j) if (g[i][j] == 1 && !vis[i][j]) {
					++cnt;
					std::queue<std::pair<int,int>> q;
					q.push({i, j});
					vis[i][j] = 1;
					while (!q.empty()) {
						auto [x, y] = q.front();
						q.pop();
						static int dx[4] = {-1, 1, 0, 0};
						static int dy[4] = {0, 0, -1, 1};
						for (int d = 0; d < 4; ++d) {
							int nx = x + dx[d], ny = y + dy[d];
							if (nx >= 0 && nx < m && ny >= 0 && ny < n && g[nx][ny] == 1 && !vis[nx][ny]) {
								vis[nx][ny] = 1;
								q.push({nx, ny});
							}
						}
					}
				}
			}
			return cnt;
		};
		if (countIslands(grid) != 1) return 0;
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) if (grid[i][j] == 1) {
				grid[i][j] = 0;
				if (countIslands(grid) != 1) {
					grid[i][j] = 1;
					return 1;
				}
				grid[i][j] = 1;
			}
		}
		return 2;
	}
};