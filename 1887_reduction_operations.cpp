#include <vector>
#include <algorithm>

using std::vector;

class Solution {
public:
	int reductionOperations(vector<int>& nums) {
		std::sort(nums.begin(), nums.end());
		int n = (int)nums.size();
		int ans = 0, lvl = 0;
		for (int i = 1; i < n; ++i) {
			if (nums[i] != nums[i - 1]) ++lvl;
			ans += lvl;
		}
		return ans;
	}
};