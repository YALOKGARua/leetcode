#include <cstdint>

class Solution {
public:
	int minimumPossibleSum(int n, int target) {
		static const long long MOD = 1000000007LL;
		long long m = std::min<long long>(n, target / 2);
		long long sumSmall = (m * (m + 1) / 2) % MOD;
		long long t = n - m;
		long long sumLarge = ((t % MOD) * (target % MOD)) % MOD;
		sumLarge = (sumLarge + ((t * (t - 1) / 2) % MOD)) % MOD;
		return (int)((sumSmall + sumLarge) % MOD);
	}
};