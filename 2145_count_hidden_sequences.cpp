#include <vector>

using std::vector;

class Solution {
public:
	int numberOfArrays(vector<int>& differences, int lower, int upper) {
		long long pref = 0;
		long long mn = 0, mx = 0;
		for (int d : differences) {
			pref += d;
			if (pref < mn) mn = pref;
			if (pref > mx) mx = pref;
		}
		long long span = mx - mn;
		long long len = (long long)upper - (long long)lower - span + 1;
		if (len < 0) return 0;
		return (int)len;
	}
};


