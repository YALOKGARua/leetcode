/*
 * @lc app=leetcode id=1223 lang=cpp
 *
 * [1223] Dice Roll Simulation
 *
 * https://leetcode.com/problems/dice-roll-simulation/description/
 *
 * algorithms
 * Hard (49.92%)
 * Likes:    967
 * Dislikes: 196
 * Total Accepted:    34.1K
 * Total Submissions: 68.3K
 * Testcase Example:  '2\n[1,1,2,2,2,3]'
 *
 * A die simulator generates a random number from 1 to 6 for each roll. You
 * introduced a constraint to the generator such that it cannot roll the number
 * i more than rollMax[i] (1-indexed) consecutive times.
 * 
 * Given an array of integers rollMax and an integer n, return the number of
 * distinct sequences that can be obtained with exact n rolls. Since the answer
 * may be too large, return it modulo 10^9 + 7.
 * 
 * Two sequences are considered different if at least one element differs from
 * each other.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 2, rollMax = [1,1,2,2,2,3]
 * Output: 34
 * Explanation: There will be 2 rolls of die, if there are no constraints on
 * the die, there are 6 * 6 = 36 possible combinations. In this case, looking
 * at rollMax array, the numbers 1 and 2 appear at most once consecutively,
 * therefore sequences (1,1) and (2,2) cannot occur, so the final answer is
 * 36-2 = 34.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 2, rollMax = [1,1,1,1,1,1]
 * Output: 30
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: n = 3, rollMax = [1,1,1,2,2,3]
 * Output: 181
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 5000
 * rollMax.length == 6
 * 1 <= rollMax[i] <= 15
 * 
 * 
 */

#include <vector>
using namespace std;

class Solution {
public:
    int dieSimulator(int n, vector<int>& rollMax) {
        const int MOD = 1e9 + 7;
        const int DICE_FACES = 6;
        
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(DICE_FACES, vector<int>(16, 0)));
        
        for (int face = 0; face < DICE_FACES; face++) {
            dp[1][face][1] = 1;
        }
        
        for (int i = 2; i <= n; i++) {
            for (int face = 0; face < DICE_FACES; face++) {
                for (int prev_face = 0; prev_face < DICE_FACES; prev_face++) {
                    for (int len = 1; len <= rollMax[prev_face]; len++) {
                        if (face != prev_face) {
                            dp[i][face][1] = (dp[i][face][1] + dp[i-1][prev_face][len]) % MOD;
                        } else if (len < rollMax[face]) {
                            dp[i][face][len+1] = (dp[i][face][len+1] + dp[i-1][prev_face][len]) % MOD;
                        }
                    }
                }
            }
        }
        
        int result = 0;
        for (int face = 0; face < DICE_FACES; face++) {
            for (int len = 1; len <= rollMax[face]; len++) {
                result = (result + dp[n][face][len]) % MOD;
            }
        }
        
        return result;
    }
};

