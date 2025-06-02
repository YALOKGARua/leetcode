/*
 * @lc app=leetcode id=1220 lang=cpp
 *
 * [1220] Count Vowels Permutation
 *
 * https://leetcode.com/problems/count-vowels-permutation/description/
 *
 * algorithms
 * Hard (61.49%)
 * Likes:    3281
 * Dislikes: 218
 * Total Accepted:    176.8K
 * Total Submissions: 287.5K
 * Testcase Example:  '1'
 *
 * Given an integer n, your task is to count how many strings of length n can
 * be formed under the following rules:
 * 
 * 
 * Each character is a lower case vowel ('a', 'e', 'i', 'o', 'u')
 * Each vowel 'a' may only be followed by an 'e'.
 * Each vowel 'e' may only be followed by an 'a' or an 'i'.
 * Each vowel 'i' may not be followed by another 'i'.
 * Each vowel 'o' may only be followed by an 'i' or a 'u'.
 * Each vowel 'u' may only be followed by an 'a'.
 * 
 * 
 * Since the answer may be too large, return it modulo 10^9 + 7.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 1
 * Output: 5
 * Explanation: All possible strings are: "a", "e", "i" , "o" and "u".
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 2
 * Output: 10
 * Explanation: All possible strings are: "ae", "ea", "ei", "ia", "ie", "io",
 * "iu", "oi", "ou" and "ua".
 * 
 * 
 * Example 3: 
 * 
 * 
 * Input: n = 5
 * Output: 68
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 2 * 10^4
 * 
 * 
 */

#include <vector>
using namespace std;

// @lc code=start
class Solution {
public:
    int countVowelPermutation(int n) {
        const int MOD = 1e9 + 7;
        
        vector<long> curr(5, 1);
        vector<long> next(5);
        
        for (int i = 2; i <= n; i++) {
            next[0] = (curr[1] + curr[2] + curr[4]) % MOD;
            next[1] = (curr[0] + curr[2]) % MOD;
            next[2] = (curr[1] + curr[3]) % MOD;
            next[3] = curr[2];
            next[4] = (curr[2] + curr[3]) % MOD;
            
            swap(curr, next);
        }
        
        long result = 0;
        for (int j = 0; j < 5; j++) {
            result = (result + curr[j]) % MOD;
        }
        
        return static_cast<int>(result);
    }
};
// @lc code=end

