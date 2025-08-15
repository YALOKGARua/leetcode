#include <vector>
#include <queue>

using std::vector;

class Solution {
public:
	int maxCandies(vector<int>& status, vector<int>& candies, vector<vector<int>>& keys, vector<vector<int>>& containedBoxes, vector<int>& initialBoxes) {
		int n = (int)status.size();
		vector<int> haveBox(n, 0), haveKey(n, 0), visited(n, 0);
		std::queue<int> q;
		for (int b : initialBoxes) haveBox[b] = 1;
		for (int i = 0; i < n; ++i) if (haveBox[i] && (status[i] == 1 || haveKey[i]) && !visited[i]) {
			q.push(i);
			visited[i] = 1;
		}
		long long total = 0;
		while (!q.empty()) {
			int box = q.front();
			q.pop();
			total += candies[box];
			for (int k : keys[box]) {
				if (!haveKey[k]) {
					haveKey[k] = 1;
					if (haveBox[k] && !visited[k]) {
						q.push(k);
						visited[k] = 1;
					}
				}
			}
			for (int b : containedBoxes[box]) {
				if (!haveBox[b]) haveBox[b] = 1;
				if ((status[b] == 1 || haveKey[b]) && !visited[b]) {
					q.push(b);
					visited[b] = 1;
				}
			}
		}
		return (int)total;
	}
};