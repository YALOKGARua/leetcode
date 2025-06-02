/*
 * @lc app=leetcode id=1240 lang=cpp
 *
 * [1240] Tiling a Rectangle with the Fewest Squares
 *
 * https://leetcode.com/problems/tiling-a-rectangle-with-the-fewest-squares/description/
 *
 * algorithms
 * Hard (54.37%)
 * Likes:    705
 * Dislikes: 576
 * Total Accepted:    25.8K
 * Total Submissions: 47.5K
 * Testcase Example:  '2\n3'
 *
 * Given a rectangle of size n x m, return the minimum number of integer-sided
 * squares that tile the rectangle.
 * 
 * 
 * Example 1:
 * 
 * 
 * 
 * 
 * Input: n = 2, m = 3
 * Output: 3
 * Explanation: 3 squares are necessary to cover the rectangle.
 * 2 (squares of 1x1)
 * 1 (square of 2x2)
 * 
 * Example 2:
 * 
 * 
 * 
 * 
 * Input: n = 5, m = 8
 * Output: 5
 * 
 * 
 * Example 3:
 * 
 * 
 * 
 * 
 * Input: n = 11, m = 13
 * Output: 6
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n, m <= 13
 * 
 * 
 */

#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
private:
    int result;
    
    void backtrack(vector<vector<bool>>& grid, int n, int m, int count) {
        if (count >= result) return;
        
        int r = -1, c = -1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!grid[i][j]) {
                    r = i;
                    c = j;
                    break;
                }
            }
            if (r != -1) break;
        }
        
        if (r == -1) {
            result = min(result, count);
            return;
        }
        
        int maxSize = min(n - r, m - c);
        for (int size = maxSize; size > 0; size--) {
            bool canPlace = true;
            for (int i = r; i < r + size && canPlace; i++) {
                for (int j = c; j < c + size && canPlace; j++) {
                    if (grid[i][j]) canPlace = false;
                }
            }
            
            if (canPlace) {
                for (int i = r; i < r + size; i++) {
                    for (int j = c; j < c + size; j++) {
                        grid[i][j] = true;
                    }
                }
                
                backtrack(grid, n, m, count + 1);
                
                for (int i = r; i < r + size; i++) {
                    for (int j = c; j < c + size; j++) {
                        grid[i][j] = false;
                    }
                }
            }
        }
    }
    
public:
    int tilingRectangle(int n, int m) {
        if (n == m) return 1;
        
        vector<vector<bool>> grid(n, vector<bool>(m, false));
        result = n * m;
        
        backtrack(grid, n, m, 0);
        
        return result;
    }
};

