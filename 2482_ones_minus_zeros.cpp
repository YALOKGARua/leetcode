#include <vector>

using std::vector;

class Solution {
public:
	vector<vector<int>> onesMinusZeros(vector<vector<int>>& grid) {
		int m = (int)grid.size();
		int n = (int)grid[0].size();
		vector<int> row(m, 0), col(n, 0);
		for (int i = 0; i < m; ++i) for (int j = 0; j < n; ++j) {
			row[i] += grid[i][j];
			col[j] += grid[i][j];
		}
		vector<vector<int>> diff(m, vector<int>(n));
		for (int i = 0; i < m; ++i) for (int j = 0; j < n; ++j) {
			diff[i][j] = 2 * row[i] + 2 * col[j] - m - n;
		}
		return diff;
	}
};