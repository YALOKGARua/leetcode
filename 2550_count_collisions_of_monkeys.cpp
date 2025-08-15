class Solution {
public:
	int monkeyMove(int n) {
		static const int MOD = 1000000007;
		long long a = 2, e = n, r = 1;
		while (e > 0) {
			if (e & 1) r = (r * a) % MOD;
			a = (a * a) % MOD;
			e >>= 1;
		}
		long long ans = (r - 2) % MOD;
		if (ans < 0) ans += MOD;
		return (int)ans;
	}
};