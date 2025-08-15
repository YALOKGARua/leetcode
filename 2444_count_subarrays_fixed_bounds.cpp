#include <vector>

using std::vector;

class Solution {
public:
	long long countSubarrays(vector<int>& nums, int minK, int maxK) {
		long long ans = 0;
		int leftBad = -1;
		int lastMin = -1;
		int lastMax = -1;
		for (int i = 0; i < (int)nums.size(); ++i) {
			int x = nums[i];
			if (x < minK || x > maxK) leftBad = i;
			if (x == minK) lastMin = i;
			if (x == maxK) lastMax = i;
			int bound = lastMin < lastMax ? lastMin : lastMax;
			if (bound > leftBad) ans += bound - leftBad;
		}
		return ans;
	}
};