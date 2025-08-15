#include <vector>

using std::vector;

class Solution {
public:
	bool canPartitionGrid(vector<vector<int>>& grid) {
		int m = (int)grid.size();
		int n = (int)grid[0].size();
		vector<long long> row(m, 0), col(n, 0);
		long long total = 0;
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				long long v = grid[i][j];
				total += v;
				row[i] += v;
				col[j] += v;
			}
		}
		if ((total & 1LL) != 0) return false;
		long long half = total >> 1;
		long long pref = 0;
		for (int i = 0; i + 1 < m; ++i) {
			pref += row[i];
			if (pref == half) return true;
		}
		pref = 0;
		for (int j = 0; j + 1 < n; ++j) {
			pref += col[j];
			if (pref == half) return true;
		}
		return false;
	}
};