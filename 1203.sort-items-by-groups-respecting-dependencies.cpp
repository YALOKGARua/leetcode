/*
 * @lc app=leetcode id=1203 lang=cpp
 *
 * [1203] Sort Items by Groups Respecting Dependencies
 *
 * https://leetcode.com/problems/sort-items-by-groups-respecting-dependencies/description/
 *
 * algorithms
 * Hard (65.63%)
 * Likes:    1834
 * Dislikes: 313
 * Total Accepted:    60.1K
 * Total Submissions: 91.5K
 * Testcase Example:  '8\n2\n[-1,-1,1,0,0,1,0,-1]\n[[],[6],[5],[6],[3,6],[],[],[]]'
 *
 * There are n items each belonging to zero or one of m groups where group[i]
 * is the group that the i-th item belongs to and it's equal to -1 if the i-th
 * item belongs to no group. The items and the groups are zero indexed. A group
 * can have no item belonging to it.
 * 
 * Return a sorted list of the items such that:
 * 
 * 
 * The items that belong to the same group are next to each other in the sorted
 * list.
 * There are some relations between these items where beforeItems[i] is a list
 * containing all the items that should come before the i-th item in the sorted
 * array (to the left of the i-th item).
 * 
 * 
 * Return any solution if there is more than one solution and return an empty
 * list if there is no solution.
 * 
 * 
 * Example 1:
 * 
 * 
 * 
 * 
 * Input: n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems =
 * [[],[6],[5],[6],[3,6],[],[],[]]
 * Output: [6,3,4,1,5,2,0,7]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems =
 * [[],[6],[5],[6],[3],[],[4],[]]
 * Output: []
 * Explanation: This is the same as example 1 except that 4 needs to be before
 * 6 in the sorted list.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= m <= n <= 3 * 10^4
 * group.length == beforeItems.length == n
 * -1 <= group[i] <= m - 1
 * 0 <= beforeItems[i].length <= n - 1
 * 0 <= beforeItems[i][j] <= n - 1
 * i != beforeItems[i][j]
 * beforeItems[i] does not contain duplicates elements.
 * 
 * 
 */

#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution {
private:
    vector<int> topoSort(vector<vector<int>>& graph, vector<int>& indegree) {
        int n = graph.size();
        vector<int> result;
        queue<int> q;
        
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        
        while (!q.empty()) {
            int curr = q.front(); q.pop();
            result.push_back(curr);
            
            for (int next : graph[curr]) {
                if (--indegree[next] == 0) {
                    q.push(next);
                }
            }
        }
        
        return result.size() == n ? result : vector<int>();
    }
    
public:
    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
        int groupId = m;
        for (int i = 0; i < n; i++) {
            if (group[i] == -1) {
                group[i] = groupId++;
            }
        }
        
        vector<vector<int>> itemGraph(n);
        vector<int> itemIndegree(n);
        
        vector<vector<int>> groupGraph(groupId);
        vector<int> groupIndegree(groupId);
        
        for (int i = 0; i < n; i++) {
            for (int before : beforeItems[i]) {
                itemGraph[before].push_back(i);
                itemIndegree[i]++;
                
                if (group[before] != group[i]) {
                    groupGraph[group[before]].push_back(group[i]);
                    groupIndegree[group[i]]++;
                }
            }
        }
        
        vector<int> groupOrder = topoSort(groupGraph, groupIndegree);
        if (groupOrder.empty()) return {};
        
        vector<int> itemOrder = topoSort(itemGraph, itemIndegree);
        if (itemOrder.empty()) return {};
        
        unordered_map<int, vector<int>> groupItems;
        for (int item : itemOrder) {
            groupItems[group[item]].push_back(item);
        }
        
        vector<int> result;
        for (int gid : groupOrder) {
            if (groupItems.count(gid)) {
                result.insert(result.end(), groupItems[gid].begin(), groupItems[gid].end());
            }
        }
        
        return result;
    }
};

