#include <vector>

using std::vector;

class Solution {
public:
	int maximumDifference(vector<int>& nums) {
		int n = (int)nums.size();
		int mn = nums[0];
		int best = -1;
		for (int i = 1; i < n; ++i) {
			if (nums[i] > mn) {
				int d = nums[i] - mn;
				if (d > best) best = d;
			}
			if (nums[i] < mn) mn = nums[i];
		}
		return best;
	}
};