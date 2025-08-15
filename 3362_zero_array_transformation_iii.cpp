#include <vector>
#include <queue>

using std::vector;

class Solution {
public:
	int maxRemoval(vector<int>& nums, vector<vector<int>>& queries) {
		int n = (int)nums.size();
		int q = (int)queries.size();
		vector<vector<int>> starts(n);
		for (auto& qr : queries) starts[qr[0]].push_back(qr[1]);
		std::priority_queue<int> cand;
		std::priority_queue<int, vector<int>, std::greater<int>> active;
		long long used = 0;
		for (int i = 0; i < n; ++i) {
			while (!active.empty() && active.top() < i) active.pop();
			for (int r : starts[i]) cand.push(r);
			int need = nums[i] - (int)active.size();
			while (need > 0) {
				while (!cand.empty() && cand.top() < i) cand.pop();
				if (cand.empty()) return -1;
				int r = cand.top();
				cand.pop();
				active.push(r);
				--need;
				++used;
			}
		}
		return q - (int)used;
	}
};