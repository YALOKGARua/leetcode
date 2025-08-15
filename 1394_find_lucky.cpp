#include <vector>

using std::vector;

class Solution {
public:
	int findLucky(vector<int>& arr) {
		vector<int> cnt(501, 0);
		for (int x : arr) if (x >= 1 && x <= 500) ++cnt[x];
		int ans = -1;
		for (int v = 1; v <= 500; ++v) if (cnt[v] == v) ans = v;
		return ans;
	}
};