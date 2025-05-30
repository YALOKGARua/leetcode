/*
 * @lc app=leetcode id=913 lang=cpp
 *
 * [913] Cat and Mouse
 *
 * https://leetcode.com/problems/cat-and-mouse/description/
 *
 * algorithms
 * Hard (33.95%)
 * Likes:    962
 * Dislikes: 172
 * Total Accepted:    22.9K
 * Total Submissions: 67.4K
 * Testcase Example:  '[[2,5],[3],[0,4,5],[1,4,5],[2,3],[0,2,3]]'
 *
 * A game on an undirected graph is played by two players, Mouse and Cat, who
 * alternate turns.
 * 
 * The graph is given as follows: graph[a] is a list of all nodes b such that
 * ab is an edge of the graph.
 * 
 * The mouse starts at node 1 and goes first, the cat starts at node 2 and goes
 * second, and there is a hole at node 0.
 * 
 * During each player's turn, they must travel along one edge of the graph that
 * meets where they are. For example, if the Mouse is at node 1, it must
 * travel to any node in graph[1].
 * 
 * Additionally, it is not allowed for the Cat to travel to the Hole (node 0).
 * 
 * Then, the game can end in three ways:
 * 
 * 
 * If ever the Cat occupies the same node as the Mouse, the Cat wins.
 * If ever the Mouse reaches the Hole, the Mouse wins.
 * If ever a position is repeated (i.e., the players are in the same position
 * as a previous turn, and it is the same player's turn to move), the game is a
 * draw.
 * 
 * 
 * Given a graph, and assuming both players play optimally, return
 * 
 * 
 * 1 if the mouse wins the game,
 * 2 if the cat wins the game, or
 * 0 if the game is a draw.
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: graph = [[2,5],[3],[0,4,5],[1,4,5],[2,3],[0,2,3]]
 * Output: 0
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: graph = [[1,3],[0],[3],[0,2]]
 * Output: 1
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 3 <= graph.length <= 50
 * 1 <= graph[i].length < graph.length
 * 0 <= graph[i][j] < graph.length
 * graph[i][j] != i
 * graph[i] is unique.
 * The mouse and the cat can always move. 
 * 
 * 
 */

#include <vector>
#include <queue>
using namespace std;

// @lc code=start
class Solution {
public:
    int catMouseGame(vector<vector<int>>& g) {
        int n = g.size();
        vector<vector<vector<int>>> color(n, vector<vector<int>>(n, vector<int>(2)));
        vector<vector<vector<int>>> degree(n, vector<vector<int>>(n, vector<int>(2)));
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                degree[i][j][0] = g[i].size();
                degree[i][j][1] = 0;
                for (int k : g[j]) if (k != 0) degree[i][j][1]++;
            }
        }
        
        queue<vector<int>> q;
        for (int i = 0; i < n; ++i) {
            for (int t = 0; t < 2; ++t) {
                color[0][i][t] = 1;
                q.push({0, i, t});
                if (i > 0) {
                    color[i][i][t] = 2;
                    q.push({i, i, t});
                }
            }
        }
        
        while (!q.empty()) {
            vector<int> s = q.front(); q.pop();
            int i = s[0], j = s[1], t = s[2];
            int c = color[i][j][t];
            
            if (t == 0) {
                for (int nj : g[j]) if (nj != 0) {
                    if (color[i][nj][1] != 0) continue;
                    if ((c == 2 && --degree[i][nj][1] == 0) || c == 1) {
                        color[i][nj][1] = c;
                        q.push({i, nj, 1});
                    }
                }
            } else {
                for (int ni : g[i]) {
                    if (color[ni][j][0] != 0) continue;
                    if ((c == 1 && --degree[ni][j][0] == 0) || c == 2) {
                        color[ni][j][0] = c;
                        q.push({ni, j, 0});
                    }
                }
            }
        }
        
        return color[1][2][0];
    }
};
// @lc code=end

