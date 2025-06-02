/*
 * @lc app=leetcode id=1249 lang=cpp
 *
 * [1249] Minimum Remove to Make Valid Parentheses
 *
 * https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/description/
 *
 * algorithms
 * Medium (70.68%)
 * Likes:    7175
 * Dislikes: 157
 * Total Accepted:    940.2K
 * Total Submissions: 1.3M
 * Testcase Example:  '"lee(t(c)o)de)"'
 *
 * Given a string s of '(' , ')' and lowercase English characters.
 * 
 * Your task is to remove the minimum number of parentheses ( '(' or ')', in
 * any positions ) so that the resulting parentheses string is valid and return
 * any valid string.
 * 
 * Formally, a parentheses string is valid if and only if:
 * 
 * 
 * It is the empty string, contains only lowercase characters, or
 * It can be written as AB (A concatenated with B), where A and B are valid
 * strings, or
 * It can be written as (A), where A is a valid string.
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "lee(t(c)o)de)"
 * Output: "lee(t(c)o)de"
 * Explanation: "lee(t(co)de)" , "lee(t(c)ode)" would also be accepted.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "a)b(c)d"
 * Output: "ab(c)d"
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "))(("
 * Output: ""
 * Explanation: An empty string is also valid.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 10^5
 * s[i] is either '(' , ')', or lowercase English letter.
 * 
 * 
 */

#include <string>
#include <stack>
#include <unordered_set>
using namespace std;

class Solution {
public:
    string minRemoveToMakeValid(string s) {
        stack<int> st;
        unordered_set<int> invalidIdx;
        
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                st.push(i);
            } else if (s[i] == ')') {
                if (!st.empty()) {
                    st.pop();
                } else {
                    invalidIdx.insert(i);
                }
            }
        }
        
        while (!st.empty()) {
            invalidIdx.insert(st.top());
            st.pop();
        }
        
        string result;
        for (int i = 0; i < s.length(); i++) {
            if (invalidIdx.find(i) == invalidIdx.end()) {
                result += s[i];
            }
        }
        
        return result;
    }
};

