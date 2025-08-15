#include <vector>
#include <unordered_map>

using std::vector;
using std::unordered_map;

class Solution {
public:
	long long countInterestingSubarrays(vector<int>& nums, int modulo, int k) {
		unordered_map<int, long long> freq;
		freq[0] = 1;
		long long pref = 0;
		long long ans = 0;
		for (int x : nums) {
			if (x % modulo == k) ++pref;
			int r = (int)(pref % modulo);
			int need = r - k;
			need %= modulo;
			if (need < 0) need += modulo;
			auto it = freq.find(need);
			if (it != freq.end()) ans += it->second;
			++freq[r];
		}
		return ans;
	}
};