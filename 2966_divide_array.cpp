#include <vector>
#include <algorithm>

using std::vector;

class Solution {
public:
	vector<vector<int>> divideArray(vector<int>& nums, int k) {
		int n = (int)nums.size();
		if (n % 3 != 0) return {};
		std::sort(nums.begin(), nums.end());
		vector<vector<int>> res;
		res.reserve(n / 3);
		for (int i = 0; i < n; i += 3) {
			if (nums[i + 2] - nums[i] > k) return {};
			res.push_back({nums[i], nums[i + 1], nums[i + 2]});
		}
		return res;
	}
};