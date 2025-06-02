/*
 * @lc app=leetcode id=1073 lang=cpp
 *
 * [1073] Adding Two Negabinary Numbers
 *
 * https://leetcode.com/problems/adding-two-negabinary-numbers/description/
 *
 * algorithms
 * Medium (36.86%)
 * Likes:    328
 * Dislikes: 127
 * Total Accepted:    20K
 * Total Submissions: 54.1K
 * Testcase Example:  '[1,1,1,1,1]\n[1,0,1]'
 *
 * Given two numbers arr1 and arr2 in base -2, return the result of adding them
 * together.
 * 
 * Each number is given in array format:  as an array of 0s and 1s, from most
 * significant bit to least significant bit.  For example, arr = [1,1,0,1]
 * represents the number (-2)^3 + (-2)^2 + (-2)^0 = -3.  A number arr in array,
 * format is also guaranteed to have no leading zeros: either arr == [0] or
 * arr[0] == 1.
 * 
 * Return the result of adding arr1 and arr2 in the same format: as an array of
 * 0s and 1s with no leading zeros.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: arr1 = [1,1,1,1,1], arr2 = [1,0,1]
 * Output: [1,0,0,0,0]
 * Explanation: arr1 represents 11, arr2 represents 5, the output represents
 * 16.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: arr1 = [0], arr2 = [0]
 * Output: [0]
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: arr1 = [0], arr2 = [1]
 * Output: [1]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= arr1.length, arr2.length <= 1000
 * arr1[i] and arr2[i] are 0 or 1
 * arr1 and arr2 have no leading zeros
 * 
 * 
 */

// @lc code=start
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> addNegabinary(vector<int>& arr1, vector<int>& arr2) {
        vector<int> result;
        int carry = 0;
        int i = arr1.size() - 1;
        int j = arr2.size() - 1;
        
        while (i >= 0 || j >= 0 || carry != 0) {
            int sum = carry;
            if (i >= 0) sum += arr1[i--];
            if (j >= 0) sum += arr2[j--];
            
            result.push_back(sum & 1);
            carry = -(sum >> 1);
        }
        
        while (result.size() > 1 && result.back() == 0) {
            result.pop_back();
        }
        
        reverse(result.begin(), result.end());
        return result;
    }
};
// @lc code=end

