#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;

class Solution {
public:
	long long numberOfPowerfulInt(long long start, long long finish, int limit, string s) {
		long long t = 0;
		for (char c : s) t = t * 10 + (c - '0');
		int m = (int)s.size();
		long long p10 = 1;
		for (int i = 0; i < m; ++i) p10 *= 10LL;
		auto countYUpTo = [&](long long L) -> long long {
			if (L < 0) return 0LL;
			vector<int> d;
			while (L > 0) {
				d.push_back((int)(L % 10));
				L /= 10;
			}
			if (d.empty()) d.push_back(0);
			std::reverse(d.begin(), d.end());
			long long dpLoose = 0, dpTight = 1;
			for (int pos = 0; pos < (int)d.size(); ++pos) {
				long long nextLoose = 0, nextTight = 0;
				if (dpTight) {
					int up = d[pos];
					int lessCount = (up > limit) ? (limit + 1) : up;
					nextLoose += dpTight * (long long)lessCount;
					if (up <= limit) nextTight += dpTight;
				}
				if (dpLoose) {
					nextLoose += dpLoose * (long long)(limit + 1);
				}
				dpLoose = nextLoose;
				dpTight = nextTight;
			}
			return dpLoose + dpTight;
		};
		auto F = [&](long long R) -> long long {
			if (R < t) return 0LL;
			long long yMax = (R - t) / p10;
			return countYUpTo(yMax);
		};
		return F(finish) - F(start - 1);
	}
};