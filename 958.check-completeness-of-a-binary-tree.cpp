/*
 * @lc app=leetcode id=958 lang=cpp
 *
 * [958] Check Completeness of a Binary Tree
 *
 * https://leetcode.com/problems/check-completeness-of-a-binary-tree/description/
 *
 * algorithms
 * Medium (58.30%)
 * Likes:    4425
 * Dislikes: 62
 * Total Accepted:    288.1K
 * Total Submissions: 494K
 * Testcase Example:  '[1,2,3,4,5,6]'
 *
 * Given the root of a binary tree, determine if it is a complete binary tree.
 * 
 * In a complete binary tree, every level, except possibly the last, is
 * completely filled, and all nodes in the last level are as far left as
 * possible. It can have between 1 and 2^h nodes inclusive at the last level
 * h.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: root = [1,2,3,4,5,6]
 * Output: true
 * Explanation: Every level before the last is full (ie. levels with
 * node-values {1} and {2, 3}), and all nodes in the last level ({4, 5, 6}) are
 * as far left as possible.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: root = [1,2,3,4,5,null,7]
 * Output: false
 * Explanation: The node with value 7 isn't as far left as possible.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the tree is in the range [1, 100].
 * 1 <= Node.val <= 1000
 * 
 * 
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
#include <queue>
using namespace std;
class Solution {
public:
    bool isCompleteTree(TreeNode* root) {
        if (!root) return true;
        
        queue<TreeNode*> q;
        q.push(root);
        bool foundNull = false;
        
        while (!q.empty()) {
            TreeNode* node = q.front(); q.pop();
            
            if (!node) {
                foundNull = true;
            } else {
                if (foundNull) return false;
                q.push(node->left);
                q.push(node->right);
            }
        }
        
        return true;
    }
};
// @lc code=end

