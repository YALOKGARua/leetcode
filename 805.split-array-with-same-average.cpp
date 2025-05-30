/*
 * @lc app=leetcode id=805 lang=cpp
 *
 * [805] Split Array With Same Average
 *
 * https://leetcode.com/problems/split-array-with-same-average/description/
 *
 * algorithms
 * Hard (25.97%)
 * Likes:    1305
 * Dislikes: 139
 * Total Accepted:    41.2K
 * Total Submissions: 158.7K
 * Testcase Example:  '[1,2,3,4,5,6,7,8]'
 *
 * You are given an integer array nums.
 * 
 * You should move each element of nums into one of the two arrays A and B such
 * that A and B are non-empty, and average(A) == average(B).
 * 
 * Return true if it is possible to achieve that and false otherwise.
 * 
 * Note that for an array arr, average(arr) is the sum of all the elements of
 * arr over the length of arr.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,2,3,4,5,6,7,8]
 * Output: true
 * Explanation: We can split the array into [1,4,5,8] and [2,3,6,7], and both
 * of them have an average of 4.5.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [3,1]
 * Output: false
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 30
 * 0 <= nums[i] <= 10^4
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    bool splitArraySameAverage(vector<int>& A) {
        int n = A.size(), s = accumulate(A.begin(), A.end(), 0);
        vector<unordered_set<int>> dp(n / 2 + 1);
        dp[0].insert(0);
        for (int a : A)
            for (int k = n / 2; k >= 1; k--)
                for (int x : dp[k - 1])
                    dp[k].insert(x + a);
        for (int k = 1; k <= n / 2; k++)
            if (s * k % n == 0 && dp[k].count(s * k / n))
                return true;
        return false;
    }
};
// @lc code=end

