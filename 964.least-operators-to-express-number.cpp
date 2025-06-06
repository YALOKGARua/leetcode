/*
 * @lc app=leetcode id=964 lang=cpp
 *
 * [964] Least Operators to Express Number
 *
 * https://leetcode.com/problems/least-operators-to-express-number/description/
 *
 * algorithms
 * Hard (48.44%)
 * Likes:    324
 * Dislikes: 71
 * Total Accepted:    11.5K
 * Total Submissions: 23.6K
 * Testcase Example:  '3\n19'
 *
 * Given a single positive integer x, we will write an expression of the form x
 * (op1) x (op2) x (op3) x ... where each operator op1, op2, etc. is either
 * addition, subtraction, multiplication, or division (+, -, *, or /). For
 * example, with x = 3, we might write 3 * 3 / 3 + 3 - 3 which is a value of
 * 3.
 * 
 * When writing such an expression, we adhere to the following
 * conventions:
 * 
 * 
 * The division operator (/) returns rational numbers.
 * There are no parentheses placed anywhere.
 * We use the usual order of operations: multiplication and division happen
 * before addition and subtraction.
 * It is not allowed to use the unary negation operator (-). For example, "x -
 * x" is a valid expression as it only uses subtraction, but "-x + x" is not
 * because it uses negation.
 * 
 * 
 * We would like to write an expression with the least number of operators such
 * that the expression equals the given target. Return the least number of
 * operators used.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: x = 3, target = 19
 * Output: 5
 * Explanation: 3 * 3 + 3 * 3 + 3 / 3.
 * The expression contains 5 operations.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: x = 5, target = 501
 * Output: 8
 * Explanation: 5 * 5 * 5 * 5 - 5 * 5 * 5 + 5 / 5.
 * The expression contains 8 operations.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: x = 100, target = 100000000
 * Output: 3
 * Explanation: 100 * 100 * 100 * 100.
 * The expression contains 3 operations.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= x <= 100
 * 1 <= target <= 2 * 10^8
 * 
 * 
 */

#include <unordered_map>
#include <cmath>
#include <climits>
using namespace std;

// @lc code=start
class Solution {
public:
    int leastOpsExpressTarget(int x, int target) {
        if (x == target) return 0;
        if (x > target) return min(target * 2 - 1, (x - target) * 2);
        
        unordered_map<long, int> memo;
        return dp(x, target, memo);
    }
    
private:
    int dp(int x, long target, unordered_map<long, int>& memo) {
        if (target == 0) return 0;
        if (target < x) return min((int)(target * 2 - 1), (int)((x - target) * 2));
        if (memo.count(target)) return memo[target];
        
        long power = x;
        int cost = 0;
        
        while (power * x <= target) {
            power *= x;
            cost++;
        }
        
        int result;
        
        if (power == target) {
            return memo[target] = cost;
        }
        
        result = cost + 1 + dp(x, target - power, memo);
        
        if (power * x - target < target) {
            result = min(result, cost + 2 + dp(x, power * x - target, memo));
        }
        
        return memo[target] = result;
    }
};
// @lc code=end

