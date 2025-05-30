/*
 * @lc app=leetcode id=834 lang=cpp
 *
 * [834] Sum of Distances in Tree
 *
 * https://leetcode.com/problems/sum-of-distances-in-tree/description/
 *
 * algorithms
 * Hard (65.32%)
 * Likes:    5738
 * Dislikes: 138
 * Total Accepted:    168.9K
 * Total Submissions: 258.6K
 * Testcase Example:  '6\n[[0,1],[0,2],[2,3],[2,4],[2,5]]'
 *
 * There is an undirected connected tree with n nodes labeled from 0 to n - 1
 * and n - 1 edges.
 * 
 * You are given the integer n and the array edges where edges[i] = [ai, bi]
 * indicates that there is an edge between nodes ai and bi in the tree.
 * 
 * Return an array answer of length n where answer[i] is the sum of the
 * distances between the i^th node in the tree and all other nodes.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
 * Output: [8,12,6,10,10,10]
 * Explanation: The tree is shown above.
 * We can see that dist(0,1) + dist(0,2) + dist(0,3) + dist(0,4) + dist(0,5)
 * equals 1 + 1 + 2 + 2 + 2 = 8.
 * Hence, answer[0] = 8, and so on.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 1, edges = []
 * Output: [0]
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: n = 2, edges = [[1,0]]
 * Output: [1,1]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 3 * 10^4
 * edges.length == n - 1
 * edges[i].length == 2
 * 0 <= ai, bi < n
 * ai != bi
 * The given input represents a valid tree.
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        vector<vector<int>> g(n);
        for (auto& e : edges) g[e[0]].push_back(e[1]), g[e[1]].push_back(e[0]);
        vector<int> res(n), sz(n, 1);
        function<void(int, int)> dfs1 = [&](int u, int p) {
            for (int v : g[u]) if (v != p) {
                dfs1(v, u);
                sz[u] += sz[v];
                res[u] += res[v] + sz[v];
            }
        };
        function<void(int, int)> dfs2 = [&](int u, int p) {
            for (int v : g[u]) if (v != p) {
                res[v] = res[u] - sz[v] + n - sz[v];
                dfs2(v, u);
            }
        };
        dfs1(0, -1);
        dfs2(0, -1);
        return res;
    }
};
// @lc code=end

