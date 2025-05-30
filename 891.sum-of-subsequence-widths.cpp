/*
 * @lc app=leetcode id=891 lang=cpp
 *
 * [891] Sum of Subsequence Widths
 *
 * https://leetcode.com/problems/sum-of-subsequence-widths/description/
 *
 * algorithms
 * Hard (38.91%)
 * Likes:    724
 * Dislikes: 172
 * Total Accepted:    24.1K
 * Total Submissions: 61.9K
 * Testcase Example:  '[2,1,3]'
 *
 * The width of a sequence is the difference between the maximum and minimum
 * elements in the sequence.
 * 
 * Given an array of integers nums, return the sum of the widths of all the
 * non-empty subsequences of nums. Since the answer may be very large, return
 * it modulo 10^9 + 7.
 * 
 * A subsequence is a sequence that can be derived from an array by deleting
 * some or no elements without changing the order of the remaining elements.
 * For example, [3,6,2,7] is a subsequence of the array [0,3,1,6,2,2,7].
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [2,1,3]
 * Output: 6
 * Explanation: The subsequences are [1], [2], [3], [2,1], [2,3], [1,3],
 * [2,1,3].
 * The corresponding widths are 0, 0, 0, 1, 1, 2, 2.
 * The sum of these widths is 6.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [2]
 * Output: 0
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^5
 * 
 * 
 */

#include <vector>
#include <algorithm>
using namespace std;

// @lc code=start
class Solution {
public:
    int sumSubseqWidths(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size(), mod = 1e9+7;
        vector<long> p(n, 1);
        for (int i = 1; i < n; ++i) p[i] = p[i-1] * 2 % mod;
        long res = 0;
        for (int i = 0; i < n; ++i)
            res = (res + (p[i] - p[n-1-i]) * nums[i]) % mod;
        return (res + mod) % mod;
    }
};
// @lc code=end

