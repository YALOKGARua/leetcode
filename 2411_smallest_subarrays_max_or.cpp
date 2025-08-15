#include <vector>

using std::vector;

class Solution {
public:
	vector<int> smallestSubarrays(vector<int>& nums) {
		int n = (int)nums.size();
		vector<int> last(31, -1);
		vector<int> ans(n);
		for (int i = n - 1; i >= 0; --i) {
			for (int b = 0; b < 31; ++b) if ((nums[i] >> b) & 1) last[b] = i;
			int far = i;
			for (int b = 0; b < 31; ++b) if (last[b] != -1 && last[b] > far) far = last[b];
			ans[i] = far - i + 1;
		}
		return ans;
	}
};