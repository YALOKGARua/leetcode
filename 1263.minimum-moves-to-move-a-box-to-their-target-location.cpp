/*
 * @lc app=leetcode id=1263 lang=cpp
 *
 * [1263] Minimum Moves to Move a Box to Their Target Location
 *
 * https://leetcode.com/problems/minimum-moves-to-move-a-box-to-their-target-location/description/
 *
 * algorithms
 * Hard (48.93%)
 * Likes:    867
 * Dislikes: 59
 * Total Accepted:    29.9K
 * Total Submissions: 61.2K
 * Testcase Example:  '[["#","#","#","#","#","#"],["#","T","#","#","#","#"],["#",".",".","B",".","#"],["#",".","#","#",".","#"],["#",".",".",".","S","#"],["#","#","#","#","#","#"]]'
 *
 * A storekeeper is a game in which the player pushes boxes around in a
 * warehouse trying to get them to target locations.
 * 
 * The game is represented by an m x n grid of characters grid where each
 * element is a wall, floor, or box.
 * 
 * Your task is to move the box 'B' to the target position 'T' under the
 * following rules:
 * 
 * 
 * The character 'S' represents the player. The player can move up, down, left,
 * right in grid if it is a floor (empty cell).
 * The character '.' represents the floor which means a free cell to walk.
 * The character '#' represents the wall which means an obstacle (impossible to
 * walk there).
 * There is only one box 'B' and one target cell 'T' in the grid.
 * The box can be moved to an adjacent free cell by standing next to the box
 * and then moving in the direction of the box. This is a push.
 * The player cannot walk through the box.
 * 
 * 
 * Return the minimum number of pushes to move the box to the target. If there
 * is no way to reach the target, return -1.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: grid = [["#","#","#","#","#","#"],
 * ⁠              ["#","T","#","#","#","#"],
 * ⁠              ["#",".",".","B",".","#"],
 * ⁠              ["#",".","#","#",".","#"],
 * ⁠              ["#",".",".",".","S","#"],
 * ⁠              ["#","#","#","#","#","#"]]
 * Output: 3
 * Explanation: We return only the number of times the box is pushed.
 * 
 * Example 2:
 * 
 * 
 * Input: grid = [["#","#","#","#","#","#"],
 * ⁠              ["#","T","#","#","#","#"],
 * ⁠              ["#",".",".","B",".","#"],
 * ⁠              ["#","#","#","#",".","#"],
 * ⁠              ["#",".",".",".","S","#"],
 * ⁠              ["#","#","#","#","#","#"]]
 * Output: -1
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: grid = [["#","#","#","#","#","#"],
 * ⁠              ["#","T",".",".","#","#"],
 * ⁠              ["#",".","#","B",".","#"],
 * ⁠              ["#",".",".",".",".","#"],
 * ⁠              ["#",".",".",".","S","#"],
 * ⁠              ["#","#","#","#","#","#"]]
 * Output: 5
 * Explanation: push the box down, left, left, up and up.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * m == grid.length
 * n == grid[i].length
 * 1 <= m, n <= 20
 * grid contains only characters '.', '#', 'S', 'T', or 'B'.
 * There is only one character 'S', 'B', and 'T' in the grid.
 * 
 * 
 */

#include <vector>
#include <queue>
#include <tuple>
#include <set>
using namespace std;

class Solution {
public:
    int minPushBox(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        int playerRow, playerCol, boxRow, boxCol, targetRow, targetCol;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 'S') {
                    playerRow = i; playerCol = j;
                } else if (grid[i][j] == 'B') {
                    boxRow = i; boxCol = j;
                } else if (grid[i][j] == 'T') {
                    targetRow = i; targetCol = j;
                }
            }
        }
        
        vector<int> dirs = {0, 1, 0, -1, 0};
        
        auto canReach = [&](int startRow, int startCol, int endRow, int endCol, int boxR, int boxC) {
            if (startRow == endRow && startCol == endCol) return true;
            
            queue<pair<int, int>> q;
            set<pair<int, int>> visited;
            
            q.push({startRow, startCol});
            visited.insert({startRow, startCol});
            
            while (!q.empty()) {
                auto [r, c] = q.front(); q.pop();
                
                for (int i = 0; i < 4; i++) {
                    int nr = r + dirs[i];
                    int nc = c + dirs[i + 1];
                    
                    if (nr >= 0 && nr < m && nc >= 0 && nc < n && 
                        grid[nr][nc] != '#' && 
                        (nr != boxR || nc != boxC) && 
                        !visited.count({nr, nc})) {
                        
                        if (nr == endRow && nc == endCol) return true;
                        
                        q.push({nr, nc});
                        visited.insert({nr, nc});
                    }
                }
            }
            
            return false;
        };
        
        queue<tuple<int, int, int, int, int>> q;
        set<tuple<int, int, int, int>> visited;
        
        q.push({boxRow, boxCol, playerRow, playerCol, 0});
        visited.insert({boxRow, boxCol, playerRow, playerCol});
        
        while (!q.empty()) {
            auto [bRow, bCol, pRow, pCol, pushes] = q.front(); q.pop();
            
            if (bRow == targetRow && bCol == targetCol) return pushes;
            
            for (int i = 0; i < 4; i++) {
                int newBoxRow = bRow + dirs[i];
                int newBoxCol = bCol + dirs[i + 1];
                
                int newPlayerRow = bRow - dirs[i];
                int newPlayerCol = bCol - dirs[i + 1];
                
                if (newBoxRow >= 0 && newBoxRow < m && newBoxCol >= 0 && newBoxCol < n && 
                    grid[newBoxRow][newBoxCol] != '#' && 
                    newPlayerRow >= 0 && newPlayerRow < m && newPlayerCol >= 0 && newPlayerCol < n && 
                    grid[newPlayerRow][newPlayerCol] != '#' && 
                    !visited.count({newBoxRow, newBoxCol, bRow, bCol})) {
                    
                    if (canReach(pRow, pCol, newPlayerRow, newPlayerCol, bRow, bCol)) {
                        q.push({newBoxRow, newBoxCol, bRow, bCol, pushes + 1});
                        visited.insert({newBoxRow, newBoxCol, bRow, bCol});
                    }
                }
            }
        }
        
        return -1;
    }
};

