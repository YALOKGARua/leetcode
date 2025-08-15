#include <vector>
#include <unordered_set>
#include <climits>

using std::vector;
using std::unordered_set;

class Solution {
public:
	int maxSum(vector<int>& nums) {
		unordered_set<int> seen;
		long long sum = 0;
		bool hasZero = false;
		int mx = INT_MIN;
		for (int x : nums) {
			if (x > 0 && !seen.count(x)) {
				seen.insert(x);
				sum += x;
			}
			if (x == 0) hasZero = true;
			if (x > mx) mx = x;
		}
		if (sum > 0) return (int)sum;
		if (hasZero) return 0;
		return mx;
	}
};