/*
 * @lc app=leetcode id=842 lang=cpp
 *
 * [842] Split Array into Fibonacci Sequence
 *
 * https://leetcode.com/problems/split-array-into-fibonacci-sequence/description/
 *
 * algorithms
 * Medium (39.65%)
 * Likes:    1159
 * Dislikes: 307
 * Total Accepted:    43.5K
 * Total Submissions: 109.7K
 * Testcase Example:  '"1101111"'
 *
 * You are given a string of digits num, such as "123456579". We can split it
 * into a Fibonacci-like sequence [123, 456, 579].
 * 
 * Formally, a Fibonacci-like sequence is a list f of non-negative integers
 * such that:
 * 
 * 
 * 0 <= f[i] < 2^31, (that is, each integer fits in a 32-bit signed integer
 * type),
 * f.length >= 3, and
 * f[i] + f[i + 1] == f[i + 2] for all 0 <= i < f.length - 2.
 * 
 * 
 * Note that when splitting the string into pieces, each piece must not have
 * extra leading zeroes, except if the piece is the number 0 itself.
 * 
 * Return any Fibonacci-like sequence split from num, or return [] if it cannot
 * be done.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: num = "1101111"
 * Output: [11,0,11,11]
 * Explanation: The output [110, 1, 111] would also be accepted.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: num = "112358130"
 * Output: []
 * Explanation: The task is impossible.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: num = "0123"
 * Output: []
 * Explanation: Leading zeroes are not allowed, so "01", "2", "3" is not
 * valid.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= num.length <= 200
 * num contains only digits.
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    vector<int> splitIntoFibonacci(string S) {
        vector<int> res;
        int n = S.size();
        for (int i = 1; i <= min(10, n - 2); i++)
            for (int j = i + 1; j <= i + min(10, n - i - 1); j++) {
                long a = stol(S.substr(0, i)), b = stol(S.substr(i, j - i));
                if ((S[0] == '0' && i > 1) || (S[i] == '0' && j - i > 1) || a > INT_MAX || b > INT_MAX) continue;
                res = {int(a), int(b)};
                int k = j;
                while (k < n) {
                    long c = (long)res[res.size() - 2] + res[res.size() - 1];
                    if (c > INT_MAX) break;
                    string cs = to_string(c);
                    if (S.substr(k, cs.size()) != cs) break;
                    res.push_back((int)c);
                    k += cs.size();
                }
                if (k == n && res.size() >= 3) return res;
            }
        return {};
    }
};
// @lc code=end

