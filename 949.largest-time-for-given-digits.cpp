/*
 * @lc app=leetcode id=949 lang=cpp
 *
 * [949] Largest Time for Given Digits
 *
 * https://leetcode.com/problems/largest-time-for-given-digits/description/
 *
 * algorithms
 * Medium (35.50%)
 * Likes:    732
 * Dislikes: 1071
 * Total Accepted:    96.5K
 * Total Submissions: 271.7K
 * Testcase Example:  '[1,2,3,4]'
 *
 * Given an array arr of 4 digits, find the latest 24-hour time that can be
 * made using each digit exactly once.
 * 
 * 24-hour times are formatted as "HH:MM", where HH is between 00 and 23, and
 * MM is between 00 and 59. The earliest 24-hour time is 00:00, and the latest
 * is 23:59.
 * 
 * Return the latest 24-hour time in "HH:MM" format. If no valid time can be
 * made, return an empty string.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: arr = [1,2,3,4]
 * Output: "23:41"
 * Explanation: The valid 24-hour times are "12:34", "12:43", "13:24", "13:42",
 * "14:23", "14:32", "21:34", "21:43", "23:14", and "23:41". Of these times,
 * "23:41" is the latest.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: arr = [5,5,5,5]
 * Output: ""
 * Explanation: There are no valid 24-hour times as "55:55" is not valid.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * arr.length == 4
 * 0 <= arr[i] <= 9
 * 
 * 
 */

// @lc code=start
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
class Solution {
public:
    string largestTimeFromDigits(vector<int>& arr) {
        sort(arr.begin(), arr.end(), greater<int>());
        do {
            if ((arr[0] * 10 + arr[1] < 24) && (arr[2] * 10 + arr[3] < 60))
                return string(1, '0' + arr[0]) + string(1, '0' + arr[1]) + ":" + 
                       string(1, '0' + arr[2]) + string(1, '0' + arr[3]);
        } while (prev_permutation(arr.begin(), arr.end()));
        return "";
    }
};
// @lc code=end

