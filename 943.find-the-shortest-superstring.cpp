/*
 * @lc app=leetcode id=943 lang=cpp
 *
 * [943] Find the Shortest Superstring
 *
 * https://leetcode.com/problems/find-the-shortest-superstring/description/
 *
 * algorithms
 * Hard (44.21%)
 * Likes:    1481
 * Dislikes: 152
 * Total Accepted:    32.2K
 * Total Submissions: 72.8K
 * Testcase Example:  '["alex","loves","leetcode"]'
 *
 * Given an array of strings words, return the smallest string that contains
 * each string in words as a substring. If there are multiple valid strings of
 * the smallest length, return any of them.
 * 
 * You may assume that no string in words is a substring of another string in
 * words.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: words = ["alex","loves","leetcode"]
 * Output: "alexlovesleetcode"
 * Explanation: All permutations of "alex","loves","leetcode" would also be
 * accepted.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: words = ["catg","ctaagt","gcta","ttca","atgcatc"]
 * Output: "gctaagttcatgcatc"
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= words.length <= 12
 * 1 <= words[i].length <= 20
 * words[i] consists of lowercase English letters.
 * All the strings of words are unique.
 * 
 * 
 */

#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    string shortestSuperstring(vector<string>& words) {
        int n = words.size();
        vector<vector<int>> overlap(n, vector<int>(n, 0));
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j) {
                    int m1 = words[i].size(), m2 = words[j].size();
                    for (int k = min(m1, m2); k > 0; --k) {
                        if (words[i].substr(m1 - k) == words[j].substr(0, k)) {
                            overlap[i][j] = k;
                            break;
                        }
                    }
                }
            }
        }
        
        vector<vector<int>> dp(1<<n, vector<int>(n, 0));
        vector<vector<int>> parent(1<<n, vector<int>(n, -1));
        
        for (int mask = 1; mask < (1<<n); ++mask) {
            for (int i = 0; i < n; ++i) {
                if ((mask & (1<<i)) == 0) continue;
                int prevMask = mask - (1<<i);
                if (prevMask == 0) {
                    dp[mask][i] = words[i].size();
                    continue;
                }
                dp[mask][i] = INT_MAX;
                for (int j = 0; j < n; ++j) {
                    if ((prevMask & (1<<j)) == 0) continue;
                    int val = dp[prevMask][j] + words[i].size() - overlap[j][i];
                    if (val < dp[mask][i]) {
                        dp[mask][i] = val;
                        parent[mask][i] = j;
                    }
                }
            }
        }
        
        int last = 0, minLen = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (dp[(1<<n)-1][i] < minLen) {
                minLen = dp[(1<<n)-1][i];
                last = i;
            }
        }
        
        vector<int> path;
        int mask = (1<<n)-1;
        while (mask > 0) {
            path.push_back(last);
            int newLast = parent[mask][last];
            mask -= (1<<last);
            last = newLast;
        }
        reverse(path.begin(), path.end());
        
        string res = words[path[0]];
        for (int i = 1; i < n; ++i) {
            int ov = overlap[path[i-1]][path[i]];
            res += words[path[i]].substr(ov);
        }
        
        return res;
    }
};

