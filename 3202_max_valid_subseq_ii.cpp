#include <vector>
#include <algorithm>

using std::vector;

class Solution {
public:
	int maximumLength(vector<int>& nums, int k) {
		int n = (int)nums.size();
		if (k == 1) return n;
		vector<int> dp(k, 0);
		int answer = 1;
		for (int c = 0; c < k; ++c) {
			std::fill(dp.begin(), dp.end(), 0);
			int best = 1;
			for (int x : nums) {
				int r = x % k;
				int rp = c - r;
				rp %= k;
				if (rp < 0) rp += k;
				int prev = dp[rp];
				int cur = dp[r];
				int val = std::max(1, prev + 1);
				if (val > cur) dp[r] = val;
				if (dp[r] > best) best = dp[r];
			}
			if (best > answer) answer = best;
		}
		return answer;
	}
};