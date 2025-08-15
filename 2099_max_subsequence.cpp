#include <vector>
#include <algorithm>

using std::vector;

class Solution {
public:
	vector<int> maxSubsequence(vector<int>& nums, int k) {
		int n = (int)nums.size();
		vector<std::pair<int,int>> a(n);
		for (int i = 0; i < n; ++i) a[i] = {nums[i], i};
		std::sort(a.begin(), a.end(), [](const auto& x, const auto& y){
			if (x.first != y.first) return x.first > y.first;
			return x.second < y.second;
		});
		vector<int> idx;
		idx.reserve(k);
		for (int i = 0; i < k; ++i) idx.push_back(a[i].second);
		std::sort(idx.begin(), idx.end());
		vector<int> res;
		res.reserve(k);
		for (int i : idx) res.push_back(nums[i]);
		return res;
	}
};


