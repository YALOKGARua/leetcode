/*
 * @lc app=leetcode id=972 lang=cpp
 *
 * [972] Equal Rational Numbers
 *
 * https://leetcode.com/problems/equal-rational-numbers/description/
 *
 * algorithms
 * Hard (44.58%)
 * Likes:    100
 * Dislikes: 218
 * Total Accepted:    8.7K
 * Total Submissions: 19.6K
 * Testcase Example:  '"0.(52)"\n"0.5(25)"'
 *
 * Given two strings s and t, each of which represents a non-negative rational
 * number, return true if and only if they represent the same number. The
 * strings may use parentheses to denote the repeating part of the rational
 * number.
 * 
 * A rational number can be represented using up to three parts: <IntegerPart>,
 * <NonRepeatingPart>, and a <RepeatingPart>. The number will be represented in
 * one of the following three ways:
 * 
 * 
 * <IntegerPart>
 * 
 * 
 * For example, 12, 0, and 123.
 * 
 * 
 * <IntegerPart><.><NonRepeatingPart>
 * 
 * For example, 0.5, 1., 2.12, and 123.0001.
 * 
 * 
 * <IntegerPart><.><NonRepeatingPart><(><RepeatingPart><)>
 * 
 * For example, 0.1(6), 1.(9), 123.00(1212).
 * 
 * 
 * 
 * 
 * The repeating portion of a decimal expansion is conventionally denoted
 * within a pair of round brackets. For example:
 * 
 * 
 * 1/6 = 0.16666666... = 0.1(6) = 0.1666(6) = 0.166(66).
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "0.(52)", t = "0.5(25)"
 * Output: true
 * Explanation: Because "0.(52)" represents 0.52525252..., and "0.5(25)"
 * represents 0.52525252525..... , the strings represent the same number.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "0.1666(6)", t = "0.166(66)"
 * Output: true
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "0.9(9)", t = "1."
 * Output: true
 * Explanation: "0.9(9)" represents 0.999999999... repeated forever, which
 * equals 1.  [See this link for an explanation.]
 * "1." represents the number 1, which is formed correctly: (IntegerPart) = "1"
 * and (NonRepeatingPart) = "".
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * Each part consists only of digits.
 * The <IntegerPart> does not have leading zeros (except for the zero
 * itself).
 * 1 <= <IntegerPart>.length <= 4
 * 0 <= <NonRepeatingPart>.length <= 4
 * 1 <= <RepeatingPart>.length <= 4
 * 
 * 
 */

// @lc code=start
#include <string>
#include <cmath>
#include <tuple>
using namespace std;

class Solution {
public:
    bool isRationalEqual(string s, string t) {
        double val1 = parseRational(s);
        double val2 = parseRational(t);
        
        return abs(val1 - val2) < 1e-10;
    }
    
private:
    tuple<string, string, string> extractParts(string s) {
        string intPart = "0";
        string nonRepeatPart = "";
        string repeatPart = "";
        
        size_t dotPos = s.find('.');
        size_t leftPos = s.find('(');
        size_t rightPos = s.find(')');
        
        if (dotPos == string::npos) {
            intPart = s;
            return {intPart, nonRepeatPart, repeatPart};
        }
        
        intPart = s.substr(0, dotPos);
        
        if (leftPos == string::npos) {
            nonRepeatPart = s.substr(dotPos + 1);
            return {intPart, nonRepeatPart, repeatPart};
        }
        
        nonRepeatPart = s.substr(dotPos + 1, leftPos - dotPos - 1);
        repeatPart = s.substr(leftPos + 1, rightPos - leftPos - 1);
        
        return {intPart, nonRepeatPart, repeatPart};
    }
    
    double parseRational(string s) {
        auto [intPart, nonRepeatPart, repeatPart] = extractParts(s);
        
        double result = stod(intPart);
        double fraction = 0.0;
        
        for (int i = 0; i < nonRepeatPart.size(); i++) {
            fraction += (nonRepeatPart[i] - '0') * pow(10, -(i + 1));
        }
        
        if (!repeatPart.empty()) {
            double repValue = 0.0;
            for (int i = 0; i < repeatPart.size(); i++) {
                repValue = repValue * 10 + (repeatPart[i] - '0');
            }
            
            double denominator = pow(10, repeatPart.size()) - 1;
            double numerator = repValue;
            
            double repFraction = numerator / denominator;
            repFraction /= pow(10, nonRepeatPart.size() + repeatPart.size() - repeatPart.size());
            
            fraction += repFraction;
        }
        
        return result + fraction;
    }
};
// @lc code=end

