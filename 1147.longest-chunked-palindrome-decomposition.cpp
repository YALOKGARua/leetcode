/*
 * @lc app=leetcode id=1147 lang=cpp
 *
 * [1147] Longest Chunked Palindrome Decomposition
 *
 * https://leetcode.com/problems/longest-chunked-palindrome-decomposition/description/
 *
 * algorithms
 * Hard (58.75%)
 * Likes:    690
 * Dislikes: 33
 * Total Accepted:    28.1K
 * Total Submissions: 47.8K
 * Testcase Example:  '"ghiabcdefhelloadamhelloabcdefghi"'
 *
 * You are given a string text. You should split it to k substrings (subtext1,
 * subtext2, ..., subtextk) such that:
 * 
 * 
 * subtexti is a non-empty string.
 * The concatenation of all the substrings is equal to text (i.e., subtext1 +
 * subtext2 + ... + subtextk == text).
 * subtexti == subtextk - i + 1 for all valid values of i (i.e., 1 <= i <=
 * k).
 * 
 * 
 * Return the largest possible value of k.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: text = "ghiabcdefhelloadamhelloabcdefghi"
 * Output: 7
 * Explanation: We can split the string on
 * "(ghi)(abcdef)(hello)(adam)(hello)(abcdef)(ghi)".
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: text = "merchant"
 * Output: 1
 * Explanation: We can split the string on "(merchant)".
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: text = "antaprezatepzapreanta"
 * Output: 11
 * Explanation: We can split the string on
 * "(a)(nt)(a)(pre)(za)(tep)(za)(pre)(a)(nt)(a)".
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= text.length <= 1000
 * text consists only of lowercase English characters.
 * 
 * 
 */

// @lc code=start
#include <string>
using namespace std;

class Solution {
public:
    int longestDecomposition(string text) {
        return solve(text, 0, text.length() - 1);
    }
    
private:
    int solve(const string& s, int left, int right) {
        if (left > right) return 0;
        if (left == right) return 1;
        
        for (int len = 1; left + len - 1 <= right - len; len++) {
            if (s.substr(left, len) == s.substr(right - len + 1, len)) {
                return 2 + solve(s, left + len, right - len);
            }
        }
        
        return 1;
    }
};
// @lc code=end

