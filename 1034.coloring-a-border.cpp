/*
 * @lc app=leetcode id=1034 lang=cpp
 *
 * [1034] Coloring A Border
 *
 * https://leetcode.com/problems/coloring-a-border/description/
 *
 * algorithms
 * Medium (49.75%)
 * Likes:    784
 * Dislikes: 916
 * Total Accepted:    42.6K
 * Total Submissions: 85.5K
 * Testcase Example:  '[[1,1],[1,2]]\n0\n0\n3'
 *
 * You are given an m x n integer matrix grid, and three integers row, col, and
 * color. Each value in the grid represents the color of the grid square at
 * that location.
 * 
 * Two squares are called adjacent if they are next to each other in any of the
 * 4 directions.
 * 
 * Two squares belong to the same connected component if they have the same
 * color and they are adjacent.
 * 
 * The border of a connected component is all the squares in the connected
 * component that are either adjacent to (at least) a square not in the
 * component, or on the boundary of the grid (the first or last row or
 * column).
 * 
 * You should color the border of the connected component that contains the
 * square grid[row][col] with color.
 * 
 * Return the final grid.
 * 
 * 
 * Example 1:
 * Input: grid = [[1,1],[1,2]], row = 0, col = 0, color = 3
 * Output: [[3,3],[3,2]]
 * Example 2:
 * Input: grid = [[1,2,2],[2,3,2]], row = 0, col = 1, color = 3
 * Output: [[1,3,3],[2,3,3]]
 * Example 3:
 * Input: grid = [[1,1,1],[1,1,1],[1,1,1]], row = 1, col = 1, color = 2
 * Output: [[2,2,2],[2,1,2],[2,2,2]]
 * 
 * 
 * Constraints:
 * 
 * 
 * m == grid.length
 * n == grid[i].length
 * 1 <= m, n <= 50
 * 1 <= grid[i][j], color <= 1000
 * 0 <= row < m
 * 0 <= col < n
 * 
 * 
 */

// @lc code=start
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    vector<vector<int>> colorBorder(vector<vector<int>>& grid, int row, int col, int color) {
        int m = grid.size();
        int n = grid[0].size();
        int originalColor = grid[row][col];
        
        if (originalColor == color) return grid;
        
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        vector<pair<int, int>> border;
        
        vector<int> dx = {-1, 1, 0, 0};
        vector<int> dy = {0, 0, -1, 1};
        
        queue<pair<int, int>> q;
        q.push({row, col});
        visited[row][col] = true;
        
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            
            bool isBorder = false;
            
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                
                if (nx < 0 || nx >= m || ny < 0 || ny >= n || grid[nx][ny] != originalColor) {
                    isBorder = true;
                } else if (!visited[nx][ny]) {
                    q.push({nx, ny});
                    visited[nx][ny] = true;
                }
            }
            
            if (isBorder) {
                border.push_back({x, y});
            }
        }
        
        for (auto [x, y] : border) {
            grid[x][y] = color;
        }
        
        return grid;
    }
};
// @lc code=end

