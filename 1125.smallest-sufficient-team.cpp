/*
 * @lc app=leetcode id=1125 lang=cpp
 *
 * [1125] Smallest Sufficient Team
 *
 * https://leetcode.com/problems/smallest-sufficient-team/description/
 *
 * algorithms
 * Hard (55.32%)
 * Likes:    2219
 * Dislikes: 57
 * Total Accepted:    68.1K
 * Total Submissions: 123.1K
 * Testcase Example:  '["java","nodejs","reactjs"]\n[["java"],["nodejs"],["nodejs","reactjs"]]'
 *
 * In a project, you have a list of required skills req_skills, and a list of
 * people. The i^th person people[i] contains a list of skills that the person
 * has.
 * 
 * Consider a sufficient team: a set of people such that for every required
 * skill in req_skills, there is at least one person in the team who has that
 * skill. We can represent these teams by the index of each person.
 * 
 * 
 * For example, team = [0, 1, 3] represents the people with skills people[0],
 * people[1], and people[3].
 * 
 * 
 * Return any sufficient team of the smallest possible size, represented by the
 * index of each person. You may return the answer in any order.
 * 
 * It is guaranteed an answer exists.
 * 
 * 
 * Example 1:
 * Input: req_skills = ["java","nodejs","reactjs"], people =
 * [["java"],["nodejs"],["nodejs","reactjs"]]
 * Output: [0,2]
 * Example 2:
 * Input: req_skills = ["algorithms","math","java","reactjs","csharp","aws"],
 * people =
 * [["algorithms","math","java"],["algorithms","math","reactjs"],["java","csharp","aws"],["reactjs","csharp"],["csharp","math"],["aws","java"]]
 * Output: [1,2]
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= req_skills.length <= 16
 * 1 <= req_skills[i].length <= 16
 * req_skills[i] consists of lowercase English letters.
 * All the strings of req_skills are unique.
 * 1 <= people.length <= 60
 * 0 <= people[i].length <= 16
 * 1 <= people[i][j].length <= 16
 * people[i][j] consists of lowercase English letters.
 * All the strings of people[i] are unique.
 * Every skill in people[i] is a skill in req_skills.
 * It is guaranteed a sufficient team exists.
 * 
 * 
 */

// @lc code=start
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
        int n = req_skills.size();
        int m = people.size();
        
        unordered_map<string, int> skillIndex;
        for (int i = 0; i < n; i++) {
            skillIndex[req_skills[i]] = i;
        }
        
        vector<int> peopleSkills(m, 0);
        for (int i = 0; i < m; i++) {
            for (string& skill : people[i]) {
                peopleSkills[i] |= (1 << skillIndex[skill]);
            }
        }
        
        int targetMask = (1 << n) - 1;
        vector<long long> dp(1 << n, (1LL << m) - 1);
        dp[0] = 0;
        
        for (int mask = 0; mask < (1 << n); mask++) {
            for (int i = 0; i < m; i++) {
                int newMask = mask | peopleSkills[i];
                
                if (newMask != mask) {
                    long long newTeam = dp[mask] | (1LL << i);
                    if (__builtin_popcountll(newTeam) < __builtin_popcountll(dp[newMask])) {
                        dp[newMask] = newTeam;
                    }
                }
            }
        }
        
        long long team = dp[targetMask];
        vector<int> result;
        for (int i = 0; i < m; i++) {
            if ((team >> i) & 1) {
                result.push_back(i);
            }
        }
        
        return result;
    }
};
// @lc code=end

