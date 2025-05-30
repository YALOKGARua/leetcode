/*
 * @lc app=leetcode id=903 lang=cpp
 *
 * [903] Valid Permutations for DI Sequence
 *
 * https://leetcode.com/problems/valid-permutations-for-di-sequence/description/
 *
 * algorithms
 * Hard (56.76%)
 * Likes:    736
 * Dislikes: 44
 * Total Accepted:    18.4K
 * Total Submissions: 32.4K
 * Testcase Example:  '"DID"'
 *
 * You are given a string s of length n where s[i] is either:
 * 
 * 
 * 'D' means decreasing, or
 * 'I' means increasing.
 * 
 * 
 * A permutation perm of n + 1 integers of all the integers in the range [0, n]
 * is called a valid permutation if for all valid i:
 * 
 * 
 * If s[i] == 'D', then perm[i] > perm[i + 1], and
 * If s[i] == 'I', then perm[i] < perm[i + 1].
 * 
 * 
 * Return the number of valid permutations perm. Since the answer may be large,
 * return it modulo 10^9 + 7.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "DID"
 * Output: 5
 * Explanation: The 5 valid permutations of (0, 1, 2, 3) are:
 * (1, 0, 3, 2)
 * (2, 0, 3, 1)
 * (2, 1, 3, 0)
 * (3, 0, 2, 1)
 * (3, 1, 2, 0)
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "D"
 * Output: 1
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == s.length
 * 1 <= n <= 200
 * s[i] is either 'I' or 'D'.
 * 
 * 
 */

#include <vector>
#include <string>
using namespace std;

// @lc code=start
class Solution {
public:
    int numPermsDISequence(string s) {
        int n = s.size(), mod = 1e9+7;
        vector<int> dp(n+1, 1), ndp(n+1);
        for (int i = 0; i < n; ++i) {
            ndp.assign(n+1, 0);
            vector<int> pref(n+2);
            for (int j = 0; j <= n-i; ++j) pref[j+1] = (pref[j] + dp[j]) % mod;
            for (int j = 0; j <= n-i-1; ++j) {
                if (s[i] == 'D') ndp[j] = (pref[n-i+1] - pref[j+1] + mod) % mod;
                else ndp[j] = pref[j+1];
            }
            dp.swap(ndp);
        }
        return dp[0];
    }
};
// @lc code=end

