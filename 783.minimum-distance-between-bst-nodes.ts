/*
 * @lc app=leetcode id=783 lang=typescript
 *
 * [783] Minimum Distance Between BST Nodes
 *
 * https://leetcode.com/problems/minimum-distance-between-bst-nodes/description/
 *
 * algorithms
 * Easy (60.24%)
 * Likes:    3579
 * Dislikes: 430
 * Total Accepted:    287.4K
 * Total Submissions: 477K
 * Testcase Example:  '[4,2,6,1,3]'
 *
 * Given the root of a Binary Search Tree (BST), return the minimum difference
 * between the values of any two different nodes in the tree.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: root = [4,2,6,1,3]
 * Output: 1
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: root = [1,0,48,null,null,12,49]
 * Output: 1
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the tree is in the range [2, 100].
 * 0 <= Node.val <= 10^5
 * 
 * 
 * 
 * Note: This question is the same as 530:
 * https://leetcode.com/problems/minimum-absolute-difference-in-bst/
 * 
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * class TreeNode {
 *     val: number
 *     left: TreeNode | null
 *     right: TreeNode | null
 *     constructor(val?: number, left?: TreeNode | null, right?: TreeNode | null) {
 *         this.val = (val===undefined ? 0 : val)
 *         this.left = (left===undefined ? null : left)
 *         this.right = (right===undefined ? null : right)
 *     }
 * }
 */

function minDiffInBST(root: TreeNode | null): number {
    const stack: TreeNode[] = []
    let node = root
    let prev = -Infinity
    let minDiff = Infinity
    
    while (node || stack.length) {
        while (node) {
            stack.push(node)
            node = node.left
        }
        node = stack.pop()!
        minDiff = Math.min(minDiff, node.val - prev)
        prev = node.val
        node = node.right
    }
    return minDiff
};
// @lc code=end

