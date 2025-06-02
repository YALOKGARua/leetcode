/*
 * @lc app=leetcode id=957 lang=cpp
 *
 * [957] Prison Cells After N Days
 *
 * https://leetcode.com/problems/prison-cells-after-n-days/description/
 *
 * algorithms
 * Medium (38.94%)
 * Likes:    1534
 * Dislikes: 1774
 * Total Accepted:    169.5K
 * Total Submissions: 435.2K
 * Testcase Example:  '[0,1,0,1,1,0,0,1]\n7'
 *
 * There are 8 prison cells in a row and each cell is either occupied or
 * vacant.
 * 
 * Each day, whether the cell is occupied or vacant changes according to the
 * following rules:
 * 
 * 
 * If a cell has two adjacent neighbors that are both occupied or both vacant,
 * then the cell becomes occupied.
 * Otherwise, it becomes vacant.
 * 
 * 
 * Note that because the prison is a row, the first and the last cells in the
 * row can't have two adjacent neighbors.
 * 
 * You are given an integer array cells where cells[i] == 1 if the i^th cell is
 * occupied and cells[i] == 0 if the i^th cell is vacant, and you are given an
 * integer n.
 * 
 * Return the state of the prison after n days (i.e., n such changes described
 * above).
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: cells = [0,1,0,1,1,0,0,1], n = 7
 * Output: [0,0,1,1,0,0,0,0]
 * Explanation: The following table summarizes the state of the prison on each
 * day:
 * Day 0: [0, 1, 0, 1, 1, 0, 0, 1]
 * Day 1: [0, 1, 1, 0, 0, 0, 0, 0]
 * Day 2: [0, 0, 0, 0, 1, 1, 1, 0]
 * Day 3: [0, 1, 1, 0, 0, 1, 0, 0]
 * Day 4: [0, 0, 0, 0, 0, 1, 0, 0]
 * Day 5: [0, 1, 1, 1, 0, 1, 0, 0]
 * Day 6: [0, 0, 1, 0, 1, 1, 0, 0]
 * Day 7: [0, 0, 1, 1, 0, 0, 0, 0]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: cells = [1,0,0,1,0,0,1,0], n = 1000000000
 * Output: [0,0,1,1,1,1,1,0]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * cells.length == 8
 * cells[i] is either 0 or 1.
 * 1 <= n <= 10^9
 * 
 * 
 */

#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

// @lc code=start
class Solution {
public:
    vector<int> prisonAfterNDays(vector<int>& cells, int n) {
        unordered_map<string, int> seen;
        
        while (n > 0) {
            string key = cellsToString(cells);
            if (seen.count(key)) {
                int cycle = seen[key] - n;
                n %= cycle;
                if (n == 0) return cells;
            } else {
                seen[key] = n;
            }
            
            n--;
            vector<int> next(8, 0);
            for (int i = 1; i < 7; ++i) {
                next[i] = cells[i-1] == cells[i+1] ? 1 : 0;
            }
            cells = next;
        }
        
        return cells;
    }
    
private:
    string cellsToString(const vector<int>& cells) {
        string res;
        for (int c : cells) {
            res += to_string(c);
        }
        return res;
    }
};
// @lc code=end

