#include <vector>

using std::vector;

class Solution {
public:
	int minimumPairRemoval(vector<int>& nums) {
		int n = (int)nums.size();
		auto ok = [&](const vector<int>& a) {
			for (int i = 1; i < (int)a.size(); ++i) if (a[i] < a[i - 1]) return false;
			return true;
		};
		int ops = 0;
		vector<int> a = nums;
		while (!ok(a)) {
			int m = (int)a.size();
			int bestIdx = 0;
			int bestSum = a[0] + a[1];
			for (int i = 1; i + 1 < m; ++i) {
				int s = a[i] + a[i + 1];
				if (s < bestSum) {
					bestSum = s;
					bestIdx = i;
				}
			}
			a[bestIdx] = a[bestIdx] + a[bestIdx + 1];
			a.erase(a.begin() + bestIdx + 1);
			++ops;
		}
		return ops;
	}
};