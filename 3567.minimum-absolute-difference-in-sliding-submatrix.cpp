class Solution {
public:
    vector<vector<int>> minAbsDiff(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> result(m - k + 1, vector<int>(n - k + 1));
        for (int i = 0; i <= m - k; ++i) {
            for (int j = 0; j <= n - k; ++j) {
                set<int> values;
                for (int r = i; r < i + k; ++r) {
                    for (int c = j; c < j + k; ++c) {
                        values.insert(grid[r][c]);
                    }
                }
                if (values.size() == 1) {
                    result[i][j] = 0;
                } else {
                    int minDiff = INT_MAX;
                    vector<int> sorted(values.begin(), values.end());
                    for (int p = 0; p < sorted.size(); ++p) {
                        for (int q = p + 1; q < sorted.size(); ++q) {
                            minDiff = min(minDiff, abs(sorted[p] - sorted[q]));
                        }
                    }
                    result[i][j] = minDiff;
                }
            }
        }
        return result;
    }
}; 