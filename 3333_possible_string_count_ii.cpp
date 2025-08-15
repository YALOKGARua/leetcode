#include <vector>
#include <string>
#include <algorithm>

using std::vector;
using std::string;

class Solution {
public:
	int possibleStringCount(string word, int k) {
		static const int MOD = 1000000007;
		int n = (int)word.size();
		vector<int> runLengths;
		int numberOfRuns = 0;
		long long totalAssignments = 1;
		for (int i = 0; i < n;) {
			int j = i;
			while (j < n && word[j] == word[i]) ++j;
			int len = j - i;
			runLengths.push_back(len);
			++numberOfRuns;
			totalAssignments = (totalAssignments * len) % MOD;
			i = j;
		}
		int minRequiredExtra = k - numberOfRuns;
		if (minRequiredExtra <= 0) return (int)totalAssignments;
		int T = minRequiredExtra;
		int maxLenConsidered = T - 1;
		vector<int> countByLength(maxLenConsidered + 1, 0);
		for (int len : runLengths) if (len <= maxLenConsidered) ++countByLength[len];
		int maxN = numberOfRuns + T;
		vector<long long> fact(maxN + 1), invfact(maxN + 1);
		auto modPow = [&](long long a, long long e) {
			long long r = 1 % MOD;
			while (e > 0) {
				if (e & 1) r = (r * a) % MOD;
				a = (a * a) % MOD;
				e >>= 1;
			}
			return r;
		};
		fact[0] = 1;
		for (int i = 1; i <= maxN; ++i) fact[i] = (fact[i - 1] * i) % MOD;
		invfact[maxN] = modPow(fact[maxN], MOD - 2);
		for (int i = maxN; i >= 1; --i) invfact[i - 1] = (invfact[i] * i) % MOD;
		auto nCk = [&](int nn, int kk) {
			if (kk < 0 || kk > nn) return 0LL;
			return ((fact[nn] * invfact[kk]) % MOD * invfact[nn - kk]) % MOD;
		};
		vector<long long> numeratorCoeff(T, 0);
		numeratorCoeff[0] = 1;
		for (int len = 1; len <= maxLenConsidered; ++len) {
			int cnt = countByLength[len];
			if (cnt == 0) continue;
			int jmax = std::min(cnt, (T - 1) / len);
			vector<long long> chooseCoeff(jmax + 1);
			for (int j = 0; j <= jmax; ++j) {
				long long c = nCk(cnt, j);
				if (j & 1) c = (MOD - c) % MOD;
				chooseCoeff[j] = c;
			}
			vector<long long> nextCoeff(T, 0);
			for (int t = 0; t < T; ++t) {
				long long sum = 0;
				int limit = std::min(jmax, t / len);
				for (int j = 0; j <= limit; ++j) {
					sum += numeratorCoeff[t - j * len] * chooseCoeff[j];
					if (sum >= (1LL << 61)) sum %= MOD;
				}
				nextCoeff[t] = sum % MOD;
			}
			numeratorCoeff.swap(nextCoeff);
		}
		vector<long long> denomComb(T, 0);
		for (int s = 0; s < T; ++s) denomComb[s] = nCk(numberOfRuns + s - 1, s);
		long long sumBelowT = 0;
		for (int d = 0; d < T; ++d) {
			long long val = 0;
			for (int t = 0; t <= d; ++t) {
				val += numeratorCoeff[t] * denomComb[d - t];
				if (val >= (1LL << 61)) val %= MOD;
			}
			sumBelowT += val % MOD;
			if (sumBelowT >= (1LL << 61)) sumBelowT %= MOD;
		}
		sumBelowT %= MOD;
		long long result = (totalAssignments - sumBelowT) % MOD;
		if (result < 0) result += MOD;
		return (int)result;
	}
};