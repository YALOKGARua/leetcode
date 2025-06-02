/*
 * @lc app=leetcode id=963 lang=cpp
 *
 * [963] Minimum Area Rectangle II
 *
 * https://leetcode.com/problems/minimum-area-rectangle-ii/description/
 *
 * algorithms
 * Medium (55.61%)
 * Likes:    402
 * Dislikes: 479
 * Total Accepted:    33.2K
 * Total Submissions: 59.7K
 * Testcase Example:  '[[1,2],[2,1],[1,0],[0,1]]'
 *
 * You are given an array of points in the X-Y plane points where points[i] =
 * [xi, yi].
 * 
 * Return the minimum area of any rectangle formed from these points, with
 * sides not necessarily parallel to the X and Y axes. If there is not any such
 * rectangle, return 0.
 * 
 * Answers within 10^-5 of the actual answer will be accepted.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: points = [[1,2],[2,1],[1,0],[0,1]]
 * Output: 2.00000
 * Explanation: The minimum area rectangle occurs at [1,2],[2,1],[1,0],[0,1],
 * with an area of 2.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: points = [[0,1],[2,1],[1,1],[1,0],[2,0]]
 * Output: 1.00000
 * Explanation: The minimum area rectangle occurs at [1,0],[1,1],[2,1],[2,0],
 * with an area of 1.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: points = [[0,3],[1,2],[3,1],[1,3],[2,1]]
 * Output: 0
 * Explanation: There is no possible rectangle to form from these points.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= points.length <= 50
 * points[i].length == 2
 * 0 <= xi, yi <= 4 * 10^4
 * All the given points are unique.
 * 
 * 
 */

#include <vector>
#include <cmath>
#include <limits>
using namespace std;

class Solution {
public:
    double minAreaFreeRect(vector<vector<int>>& points) {
        int n = points.size();
        double result = numeric_limits<double>::max();
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (j == i) continue;
                for (int k = 0; k < n; k++) {
                    if (k == i || k == j) continue;
                    
                    vector<int> p1 = points[i];
                    vector<int> p2 = points[j];
                    vector<int> p3 = points[k];
                    
                    int v1x = p2[0] - p1[0], v1y = p2[1] - p1[1];
                    int v2x = p3[0] - p1[0], v2y = p3[1] - p1[1];
                    
                    if (v1x * v2x + v1y * v2y == 0) {
                        for (int l = 0; l < n; l++) {
                            if (l == i || l == j || l == k) continue;
                            
                            vector<int> p4 = points[l];
                            
                            int v3x = p4[0] - p3[0], v3y = p4[1] - p3[1];
                            int v4x = p4[0] - p2[0], v4y = p4[1] - p2[1];
                            
                            if (v1x == v3x && v1y == v3y && v2x == v4x && v2y == v4y) {
                                double area = sqrt(1.0 * v1x * v1x + v1y * v1y) * 
                                              sqrt(1.0 * v2x * v2x + v2y * v2y);
                                result = min(result, area);
                            }
                        }
                    }
                }
            }
        }
        
        return result == numeric_limits<double>::max() ? 0 : result;
    }
};

