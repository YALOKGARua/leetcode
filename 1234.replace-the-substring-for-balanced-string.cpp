/*
 * @lc app=leetcode id=1234 lang=cpp
 *
 * [1234] Replace the Substring for Balanced String
 *
 * https://leetcode.com/problems/replace-the-substring-for-balanced-string/description/
 *
 * algorithms
 * Medium (39.48%)
 * Likes:    1244
 * Dislikes: 220
 * Total Accepted:    40.8K
 * Total Submissions: 103.4K
 * Testcase Example:  '"QWER"'
 *
 * You are given a string s of length n containing only four kinds of
 * characters: 'Q', 'W', 'E', and 'R'.
 * 
 * A string is said to be balanced if each of its characters appears n / 4
 * times where n is the length of the string.
 * 
 * Return the minimum length of the substring that can be replaced with any
 * other string of the same length to make s balanced. If s is already
 * balanced, return 0.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "QWER"
 * Output: 0
 * Explanation: s is already balanced.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "QQWE"
 * Output: 1
 * Explanation: We need to replace a 'Q' to 'R', so that "RQWE" (or "QRWE") is
 * balanced.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "QQQW"
 * Output: 2
 * Explanation: We can replace the first "QQ" to "ER". 
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == s.length
 * 4 <= n <= 10^5
 * n is a multiple of 4.
 * s contains only 'Q', 'W', 'E', and 'R'.
 * 
 * 
 */

#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

// @lc code=start
class Solution {
public:
    int balancedString(string s) {
        int n = s.length();
        int target = n / 4;
        
        unordered_map<char, int> count = {{'Q', 0}, {'W', 0}, {'E', 0}, {'R', 0}};
        
        for (char c : s) {
            count[c]++;
        }
        
        bool isBalanced = true;
        for (auto& [c, freq] : count) {
            if (freq != target) {
                isBalanced = false;
                break;
            }
        }
        
        if (isBalanced) return 0;
        
        int left = 0;
        int result = n;
        
        for (int right = 0; right < n; right++) {
            count[s[right]]--;
            
            while (left <= right && 
                   count['Q'] <= target && 
                   count['W'] <= target && 
                   count['E'] <= target && 
                   count['R'] <= target) {
                result = min(result, right - left + 1);
                count[s[left]]++;
                left++;
            }
        }
        
        return result;
    }
};
// @lc code=end

