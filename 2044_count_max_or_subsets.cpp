#include <vector>

using std::vector;

class Solution {
public:
	int countMaxOrSubsets(vector<int>& nums) {
		int n = (int)nums.size();
		int target = 0;
		for (int v : nums) target |= v;
		int total = 1 << n;
		int count = 0;
		for (int mask = 1; mask < total; ++mask) {
			int value = 0;
			for (int i = 0; i < n; ++i) if (mask & (1 << i)) value |= nums[i];
			if (value == target) ++count;
		}
		return count;
	}
};