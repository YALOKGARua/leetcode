/*
 * @lc app=leetcode id=1012 lang=cpp
 *
 * [1012] Numbers With Repeated Digits
 *
 * https://leetcode.com/problems/numbers-with-repeated-digits/description/
 *
 * algorithms
 * Hard (43.37%)
 * Likes:    806
 * Dislikes: 89
 * Total Accepted:    20.5K
 * Total Submissions: 47.3K
 * Testcase Example:  '20'
 *
 * Given an integer n, return the number of positive integers in the range [1,
 * n] that have at least one repeated digit.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 20
 * Output: 1
 * Explanation: The only positive number (<= 20) with at least 1 repeated digit
 * is 11.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 100
 * Output: 10
 * Explanation: The positive numbers (<= 100) with atleast 1 repeated digit are
 * 11, 22, 33, 44, 55, 66, 77, 88, 99, and 100.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: n = 1000
 * Output: 262
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 10^9
 * 
 * 
 */

// @lc code=start
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int numDupDigitsAtMostN(int n) {
        vector<int> digits;
        int temp = n;
        while (temp) {
            digits.insert(digits.begin(), temp % 10);
            temp /= 10;
        }
        
        int uniqueCount = 0;
        
        for (int len = 1; len < digits.size(); len++) {
            uniqueCount += countUniqueWithLength(len);
        }
        
        vector<bool> used(10, false);
        uniqueCount += dfs(digits, 0, used, true);
        
        return n - uniqueCount;
    }
    
private:
    int countUniqueWithLength(int len) {
        if (len == 0) return 1;
        if (len == 1) return 9;
        
        int res = 9;
        for (int i = 0, j = 9; i < len - 1; i++, j--) {
            res *= j;
        }
        return res;
    }
    
    int dfs(vector<int>& digits, int idx, vector<bool>& used, bool isLimit) {
        if (idx == digits.size()) return 1;
        
        int count = 0;
        int limit = isLimit ? digits[idx] : 9;
        
        for (int d = 0; d <= limit; d++) {
            if (idx == 0 && d == 0) continue;
            
            if (!used[d]) {
                used[d] = true;
                count += dfs(digits, idx + 1, used, isLimit && d == limit);
                used[d] = false;
            }
        }
        
        return count;
    }
};
// @lc code=end


