/*
 * @lc app=leetcode id=1104 lang=cpp
 *
 * [1104] Path In Zigzag Labelled Binary Tree
 *
 * https://leetcode.com/problems/path-in-zigzag-labelled-binary-tree/description/
 *
 * algorithms
 * Medium (75.49%)
 * Likes:    1518
 * Dislikes: 326
 * Total Accepted:    50K
 * Total Submissions: 66.3K
 * Testcase Example:  '14'
 *
 * In an infinite binary tree where every node has two children, the nodes are
 * labelled in row order.
 * 
 * In the odd numbered rows (ie., the first, third, fifth,...), the labelling
 * is left to right, while in the even numbered rows (second, fourth,
 * sixth,...), the labelling is right to left.
 * 
 * 
 * 
 * Given the label of a node in this tree, return the labels in the path from
 * the root of the tree to the node with that label.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: label = 14
 * Output: [1,3,4,14]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: label = 26
 * Output: [1,2,6,10,26]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= label <= 10^6
 * 
 * 
 */

// @lc code=start
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> pathInZigZagTree(int label) {
        vector<int> result;
        
        int level = log2(label) + 1;
        
        while (label >= 1) {
            result.push_back(label);
            
            int levelMax = (1 << level) - 1;
            int levelMin = 1 << (level - 1);
            
            int parent = (levelMax + levelMin - label) / 2;
            
            label = parent;
            level--;
        }
        
        reverse(result.begin(), result.end());
        return result;
    }
};
// @lc code=end

