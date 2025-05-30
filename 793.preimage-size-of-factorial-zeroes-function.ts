/*
 * @lc app=leetcode id=793 lang=typescript
 *
 * [793] Preimage Size of Factorial Zeroes Function
 *
 * https://leetcode.com/problems/preimage-size-of-factorial-zeroes-function/description/
 *
 * algorithms
 * Hard (45.66%)
 * Likes:    454
 * Dislikes: 102
 * Total Accepted:    21.5K
 * Total Submissions: 47K
 * Testcase Example:  '0'
 *
 * Let f(x) be the number of zeroes at the end of x!. Recall that x! = 1 * 2 *
 * 3 * ... * x and by convention, 0! = 1.
 * 
 * 
 * For example, f(3) = 0 because 3! = 6 has no zeroes at the end, while f(11) =
 * 2 because 11! = 39916800 has two zeroes at the end.
 * 
 * 
 * Given an integer k, return the number of non-negative integers x have the
 * property that f(x) = k.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: k = 0
 * Output: 5
 * Explanation: 0!, 1!, 2!, 3!, and 4! end with k = 0 zeroes.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: k = 5
 * Output: 0
 * Explanation: There is no x such that x! ends in k = 5 zeroes.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: k = 3
 * Output: 5
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 0 <= k <= 10^9
 * 
 * 
 */

// @lc code=start
function preimageSizeFZF(k: number): number {
    function z(n: number) {
        let t = 0;
        while (n > 0) {
            n = Math.floor(n / 5);
            t += n;
        }
        return t;
    }
    function f(x: number) {
        let l = 0, r = 5 * x + 5;
        while (l < r) {
            let m = (l + r) >> 1;
            z(m) < x ? l = m + 1 : r = m;
        }
        return l;
    }
    return f(k + 1) - f(k);
}
// @lc code=end

