#include <string>
#include <algorithm>

using std::string;

class Solution {
public:
	int maxDistance(string s, int k) {
		auto calc = [&](int sx, int sy) {
			long long ans = 0;
			long long pref = 0;
			int neg = 0;
			for (char c : s) {
				int v;
				switch (c) {
					case 'N': v = sy; break;
					case 'S': v = -sy; break;
					case 'E': v = sx; break;
					default: v = -sx; break;
				}
				pref += v;
				if (v == -1) ++neg;
				long long cur = pref + 2LL * std::min(k, neg);
				if (cur > ans) ans = cur;
			}
			return (int)ans;
		};
		int best = 0;
		best = std::max(best, calc(1, 1));
		best = std::max(best, calc(1, -1));
		best = std::max(best, calc(-1, 1));
		best = std::max(best, calc(-1, -1));
		return best;
	}
};