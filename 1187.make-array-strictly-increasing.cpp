/*
 * @lc app=leetcode id=1187 lang=cpp
 *
 * [1187] Make Array Strictly Increasing
 *
 * https://leetcode.com/problems/make-array-strictly-increasing/description/
 *
 * algorithms
 * Hard (57.83%)
 * Likes:    2287
 * Dislikes: 50
 * Total Accepted:    62.5K
 * Total Submissions: 108K
 * Testcase Example:  '[1,5,3,6,7]\n[1,3,2,4]'
 *
 * Given two integer arrays arr1 and arr2, return the minimum number of
 * operations (possibly zero) needed to make arr1 strictly increasing.
 * 
 * In one operation, you can choose two indices 0 <= i < arr1.length and 0 <= j
 * < arr2.length and do the assignment arr1[i] = arr2[j].
 * 
 * If there is no way to make arr1 strictly increasing, return -1.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: arr1 = [1,5,3,6,7], arr2 = [1,3,2,4]
 * Output: 1
 * Explanation: Replace 5 with 2, then arr1 = [1, 2, 3, 6, 7].
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: arr1 = [1,5,3,6,7], arr2 = [4,3,1]
 * Output: 2
 * Explanation: Replace 5 with 3 and then replace 3 with 4. arr1 = [1, 3, 4, 6,
 * 7].
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: arr1 = [1,5,3,6,7], arr2 = [1,6,3,3]
 * Output: -1
 * Explanation: You can't make arr1 strictly increasing.
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= arr1.length, arr2.length <= 2000
 * 0 <= arr1[i], arr2[i] <= 10^9
 * 
 * 
 * 
 * 
 */

#include <vector>
#include <map>
#include <algorithm>
#include <climits>
using namespace std;

// @lc code=start
class Solution {
public:
    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
        sort(arr2.begin(), arr2.end());
        arr2.erase(unique(arr2.begin(), arr2.end()), arr2.end());
        
        map<int, int> dp;
        dp[INT_MIN] = 0;
        
        for (int num : arr1) {
            map<int, int> nextDp;
            
            for (auto& [prevVal, ops] : dp) {
                if (num > prevVal) {
                    nextDp[num] = min(nextDp.count(num) ? nextDp[num] : INT_MAX, ops);
                }
                
                auto it = upper_bound(arr2.begin(), arr2.end(), prevVal);
                if (it != arr2.end()) {
                    int replaceOps = ops + 1;
                    nextDp[*it] = min(nextDp.count(*it) ? nextDp[*it] : INT_MAX, replaceOps);
                }
            }
            
            if (nextDp.empty()) return -1;
            dp = move(nextDp);
        }
        
        int result = INT_MAX;
        for (auto& [val, ops] : dp) {
            result = min(result, ops);
        }
        
        return result;
    }
};
// @lc code=end

