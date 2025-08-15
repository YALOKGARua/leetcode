#include <vector>
#include <algorithm>

using std::vector;

class Solution {
public:
	long long maximumTripletValue(vector<int>& nums) {
		int n = (int)nums.size();
		vector<int> suf(n);
		suf[n - 1] = nums[n - 1];
		for (int i = n - 2; i >= 0; --i) suf[i] = std::max(nums[i], suf[i + 1]);
		int preMax = nums[0];
		long long best = 0;
		for (int j = 1; j + 1 < n; ++j) {
			long long diff = (long long)preMax - nums[j];
			long long cand = diff * (long long)suf[j + 1];
			if (cand > best) best = cand;
			if (nums[j] > preMax) preMax = nums[j];
		}
		return best;
	}
};


