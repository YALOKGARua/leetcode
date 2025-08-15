#include <vector>
#include <climits>

using std::vector;

class Solution {
public:
	int maximumJumps(vector<int>& nums, int target) {
		int n = (int)nums.size();
		vector<int> dp(n, INT_MIN / 2);
		dp[0] = 0;
		for (int i = 1; i < n; ++i) {
			for (int j = 0; j < i; ++j) {
				long long diff = (long long)nums[i] - (long long)nums[j];
				if (diff >= -(long long)target && diff <= (long long)target && dp[j] > INT_MIN / 4) {
					if (dp[j] + 1 > dp[i]) dp[i] = dp[j] + 1;
				}
			}
		}
		return dp[n - 1] < 0 ? -1 : dp[n - 1];
	}
};