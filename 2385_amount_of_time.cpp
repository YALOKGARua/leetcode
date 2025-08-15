#include <unordered_map>
#include <vector>
#include <queue>

using std::unordered_map;
using std::vector;
using std::queue;

class Solution {
public:
	int amountOfTime(TreeNode* root, int start) {
		unordered_map<int, vector<int>> g;
		build(root, g);
		unordered_map<int, int> seen;
		queue<int> q;
		q.push(start);
		seen[start] = 1;
		int minutes = -1;
		while (!q.empty()) {
			int sz = (int)q.size();
			while (sz--) {
				int u = q.front();
				q.pop();
				for (int v : g[u]) if (!seen[v]) { seen[v] = 1; q.push(v); }
			}
			++minutes;
		}
		if (minutes < 0) minutes = 0;
		return minutes;
	}

private:
	void build(TreeNode* node, unordered_map<int, vector<int>>& g) {
		if (!node) return;
		if (node->left) {
			g[node->val].push_back(node->left->val);
			g[node->left->val].push_back(node->val);
		}
		if (node->right) {
			g[node->val].push_back(node->right->val);
			g[node->right->val].push_back(node->val);
		}
		build(node->left, g);
		build(node->right, g);
	}
};