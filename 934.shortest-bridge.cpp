/*
 * @lc app=leetcode id=934 lang=cpp
 *
 * [934] Shortest Bridge
 *
 * https://leetcode.com/problems/shortest-bridge/description/
 *
 * algorithms
 * Medium (58.58%)
 * Likes:    5595
 * Dislikes: 217
 * Total Accepted:    244.8K
 * Total Submissions: 417.9K
 * Testcase Example:  '[[0,1],[1,0]]'
 *
 * You are given an n x n binary matrix grid where 1 represents land and 0
 * represents water.
 * 
 * An island is a 4-directionally connected group of 1's not connected to any
 * other 1's. There are exactly two islands in grid.
 * 
 * You may change 0's to 1's to connect the two islands to form one island.
 * 
 * Return the smallest number of 0's you must flip to connect the two
 * islands.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: grid = [[0,1],[1,0]]
 * Output: 1
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: grid = [[0,1,0],[0,0,0],[0,0,1]]
 * Output: 2
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: grid = [[1,1,1,1,1],[1,0,0,0,1],[1,0,1,0,1],[1,0,0,0,1],[1,1,1,1,1]]
 * Output: 1
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == grid.length == grid[i].length
 * 2 <= n <= 100
 * grid[i][j] is either 0 or 1.
 * There are exactly two islands in grid.
 * 
 * 
 */

// @lc code=start
#include <vector>
#include <queue>
#include <functional>
using namespace std;
class Solution {
public:
    int shortestBridge(vector<vector<int>>& g) {
        int n = g.size(), dir[5] = {0,1,0,-1,0};
        queue<pair<int,int>> q;
        bool found = false;
        function<void(int,int)> dfs = [&](int i, int j) {
            if (i < 0 || j < 0 || i >= n || j >= n || g[i][j] != 1) return;
            g[i][j] = 2;
            q.emplace(i, j);
            for (int d = 0; d < 4; ++d) dfs(i + dir[d], j + dir[d+1]);
        };
        
        for (int i = 0; i < n && !found; ++i)
            for (int j = 0; j < n && !found; ++j)
                if (g[i][j] == 1) dfs(i, j), found = true;
        int level = 0;
        while (!q.empty()) {
            int sz = q.size();
            while (sz--) {
                auto [i, j] = q.front(); q.pop();
                for (int d = 0; d < 4; ++d) {
                    int ni = i + dir[d], nj = j + dir[d+1];
                    if (ni < 0 || nj < 0 || ni >= n || nj >= n || g[ni][nj] == 2) continue;
                    if (g[ni][nj] == 1) return level;
                    g[ni][nj] = 2;
                    q.emplace(ni, nj);
                }
            }
            ++level;
        }
        return -1;
    }
};
// @lc code=end

