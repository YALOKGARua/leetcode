/*
 * @lc app=leetcode id=955 lang=cpp
 *
 * [955] Delete Columns to Make Sorted II
 *
 * https://leetcode.com/problems/delete-columns-to-make-sorted-ii/description/
 *
 * algorithms
 * Medium (35.59%)
 * Likes:    680
 * Dislikes: 95
 * Total Accepted:    22.6K
 * Total Submissions: 63.3K
 * Testcase Example:  '["ca","bb","ac"]'
 *
 * You are given an array of n strings strs, all of the same length.
 * 
 * We may choose any deletion indices, and we delete all the characters in
 * those indices for each string.
 * 
 * For example, if we have strs = ["abcdef","uvwxyz"] and deletion indices {0,
 * 2, 3}, then the final array after deletions is ["bef", "vyz"].
 * 
 * Suppose we chose a set of deletion indices answer such that after deletions,
 * the final array has its elements in lexicographic order (i.e., strs[0] <=
 * strs[1] <= strs[2] <= ... <= strs[n - 1]). Return the minimum possible value
 * of answer.length.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: strs = ["ca","bb","ac"]
 * Output: 1
 * Explanation: 
 * After deleting the first column, strs = ["a", "b", "c"].
 * Now strs is in lexicographic order (ie. strs[0] <= strs[1] <= strs[2]).
 * We require at least 1 deletion since initially strs was not in lexicographic
 * order, so the answer is 1.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: strs = ["xc","yb","za"]
 * Output: 0
 * Explanation: 
 * strs is already in lexicographic order, so we do not need to delete
 * anything.
 * Note that the rows of strs are not necessarily in lexicographic order:
 * i.e., it is NOT necessarily true that (strs[0][0] <= strs[0][1] <= ...)
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: strs = ["zyx","wvu","tsr"]
 * Output: 3
 * Explanation: We have to delete every column.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == strs.length
 * 1 <= n <= 100
 * 1 <= strs[i].length <= 100
 * strs[i] consists of lowercase English letters.
 * 
 * 
 */

#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        int n = strs.size(), m = strs[0].size(), res = 0;
        vector<bool> sorted(n-1, false);
        
        for (int j = 0; j < m; ++j) {
            vector<bool> new_sorted = sorted;
            bool need_delete = false;
            
            for (int i = 0; i < n-1; ++i) {
                if (sorted[i]) continue;
                if (strs[i][j] > strs[i+1][j]) {
                    need_delete = true;
                    break;
                }
                if (strs[i][j] < strs[i+1][j]) {
                    new_sorted[i] = true;
                }
            }
            
            if (need_delete) {
                ++res;
            } else {
                sorted = new_sorted;
            }
        }
        
        return res;
    }
};

