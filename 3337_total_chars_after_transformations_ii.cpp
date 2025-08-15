#include <vector>
#include <string>

using std::vector;
using std::string;

class Solution {
public:
	int lengthAfterTransformations(string s, int t, vector<int>& nums) {
		static const int MOD = 1000000007;
		int n = (int)s.size();
		vector<int> cnt(26, 0);
		for (char c : s) ++cnt[c - 'a'];
		vector<vector<int>> M(26, vector<int>(26, 0));
		for (int i = 0; i < 26; ++i) {
			for (int k = 1; k <= nums[i]; ++k) {
				int j = (i + k) % 26;
				int v = M[i][j] + 1;
				if (v >= MOD) v -= MOD;
				M[i][j] = v;
			}
		}
		auto matMul = [&](const vector<vector<int>>& A, const vector<vector<int>>& B) {
			vector<vector<int>> C(26, vector<int>(26, 0));
			for (int i = 0; i < 26; ++i) {
				for (int k = 0; k < 26; ++k) if (A[i][k]) {
					long long aik = A[i][k];
					for (int j = 0; j < 26; ++j) if (B[k][j]) {
						C[i][j] = (C[i][j] + (int)(aik * B[k][j] % MOD)) % MOD;
					}
				}
			}
			return C;
		};
		auto matVec = [&](const vector<vector<int>>& A, const vector<int>& v) {
			vector<int> r(26, 0);
			for (int i = 0; i < 26; ++i) {
				long long sum = 0;
				for (int j = 0; j < 26; ++j) if (A[i][j] && v[j]) {
					sum += (long long)A[i][j] * v[j];
					if (sum >= (1LL << 61)) sum %= MOD;
				}
				r[i] = (int)(sum % MOD);
			}
			return r;
		};
		vector<int> vec(26, 1);
		vector<vector<int>> P = M;
		long long e = t;
		while (e > 0) {
			if (e & 1) vec = matVec(P, vec);
			P = matMul(P, P);
			e >>= 1;
		}
		long long ans = 0;
		for (int i = 0; i < 26; ++i) if (cnt[i]) {
			ans += (long long)cnt[i] * vec[i];
			ans %= MOD;
		}
		return (int)ans;
	}
};