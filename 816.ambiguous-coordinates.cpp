/*
 * @lc app=leetcode id=816 lang=cpp
 *
 * [816] Ambiguous Coordinates
 *
 * https://leetcode.com/problems/ambiguous-coordinates/description/
 *
 * algorithms
 * Medium (55.85%)
 * Likes:    331
 * Dislikes: 666
 * Total Accepted:    32.4K
 * Total Submissions: 58K
 * Testcase Example:  '"(123)"'
 *
 * We had some 2-dimensional coordinates, like "(1, 3)" or "(2, 0.5)". Then, we
 * removed all commas, decimal points, and spaces and ended up with the string
 * s.
 * 
 * 
 * For example, "(1, 3)" becomes s = "(13)" and "(2, 0.5)" becomes s =
 * "(205)".
 * 
 * 
 * Return a list of strings representing all possibilities for what our
 * original coordinates could have been.
 * 
 * Our original representation never had extraneous zeroes, so we never started
 * with numbers like "00", "0.0", "0.00", "1.0", "001", "00.01", or any other
 * number that can be represented with fewer digits. Also, a decimal point
 * within a number never occurs without at least one digit occurring before it,
 * so we never started with numbers like ".1".
 * 
 * The final answer list can be returned in any order. All coordinates in the
 * final answer have exactly one space between them (occurring after the
 * comma.)
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "(123)"
 * Output: ["(1, 2.3)","(1, 23)","(1.2, 3)","(12, 3)"]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "(0123)"
 * Output: ["(0, 1.23)","(0, 12.3)","(0, 123)","(0.1, 2.3)","(0.1, 23)","(0.12,
 * 3)"]
 * Explanation: 0.0, 00, 0001 or 00.01 are not allowed.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "(00011)"
 * Output: ["(0, 0.011)","(0.001, 1)"]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 4 <= s.length <= 12
 * s[0] == '(' and s[s.length - 1] == ')'.
 * The rest of s are digits.
 * 
 * 
 */

// @lc code=start
class Solution {
    vector<string> generate(const string& s) {
        vector<string> res;
        if (s.size() == 1 || s[0] != '0') res.push_back(s);
        for (int i = 1; i < s.size(); i++) {
            string l = s.substr(0, i), r = s.substr(i);
            if ((l.size() == 1 || l[0] != '0') && r.back() != '0')
                res.push_back(l + "." + r);
        }
        return res;
    }
public:
    vector<string> ambiguousCoordinates(string s) {
        vector<string> res;
        int n = s.size();
        for (int i = 1; i < n - 2; i++) {
            string left = s.substr(1, i);
            string right = s.substr(i + 1, n - i - 2);
            vector<string> left_res = generate(left);
            vector<string> right_res = generate(right);
            for (auto& l : left_res)
                for (auto& r : right_res)
                    res.push_back("(" + l + ", " + r + ")");
        }
        return res;
    }
};
// @lc code=end

