/*
 * @lc app=leetcode id=906 lang=cpp
 *
 * [906] Super Palindromes
 *
 * https://leetcode.com/problems/super-palindromes/description/
 *
 * algorithms
 * Hard (39.28%)
 * Likes:    368
 * Dislikes: 422
 * Total Accepted:    26.4K
 * Total Submissions: 67.3K
 * Testcase Example:  '"4"\n"1000"'
 *
 * Let's say a positive integer is a super-palindrome if it is a palindrome,
 * and it is also the square of a palindrome.
 * 
 * Given two positive integers left and right represented as strings, return
 * the number of super-palindromes integers in the inclusive range [left,
 * right].
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: left = "4", right = "1000"
 * Output: 4
 * Explanation: 4, 9, 121, and 484 are superpalindromes.
 * Note that 676 is not a superpalindrome: 26 * 26 = 676, but 26 is not a
 * palindrome.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: left = "1", right = "2"
 * Output: 1
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= left.length, right.length <= 18
 * left and right consist of only digits.
 * left and right cannot have leading zeros.
 * left and right represent integers in the range [1, 10^18 - 1].
 * left is less than or equal to right.
 * 
 * 
 */

#include <string>
#include <algorithm>
using namespace std;

// @lc code=start
class Solution {
public:
    int superpalindromesInRange(string left, string right) {
        long l = stoll(left), r = stoll(right), res = 0;
        for (int k = 1; k < 100000; ++k) {
            string s = to_string(k), rs(s.rbegin(), s.rend());
            string p1 = s + rs;
            long v1 = stoll(p1);
            v1 *= v1;
            if (v1 > r) break;
            string t1 = to_string(v1);
            if (v1 >= l && equal(t1.begin(), t1.end(), t1.rbegin())) ++res;
        }
        for (int k = 1; k < 100000; ++k) {
            string s = to_string(k), rs(s.rbegin(), s.rend());
            string p2 = s + rs.substr(1);
            long v2 = stoll(p2);
            v2 *= v2;
            if (v2 > r) break;
            string t2 = to_string(v2);
            if (v2 >= l && equal(t2.begin(), t2.end(), t2.rbegin())) ++res;
        }
        return res;
    }
};
// @lc code=end

