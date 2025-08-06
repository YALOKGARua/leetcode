class Solution {
public:
    vector<vector<int>> differenceOfDistinctValues(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> result(m, vector<int>(n));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                set<int> leftAbove, rightBelow;
                int r = i - 1, c = j - 1;
                while (r >= 0 && c >= 0) {
                    leftAbove.insert(grid[r][c]);
                    r--;
                    c--;
                }
                r = i + 1, c = j + 1;
                while (r < m && c < n) {
                    rightBelow.insert(grid[r][c]);
                    r++;
                    c++;
                }
                result[i][j] = abs((int)leftAbove.size() - (int)rightBelow.size());
            }
        }
        return result;
    }
}; 