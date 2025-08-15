#include <vector>
#include <algorithm>

using std::vector;

class Solution {
public:
	int maxCollectedFruits(vector<vector<int>>& fruits) {
		int n = (int)fruits.size();
		long long diag = 0;
		for (int i = 0; i < n; ++i) diag += fruits[i][i];
		const long long NEG = (long long)-4e18;
		vector<vector<long long>> dp2(n, vector<long long>(n, NEG));
		vector<vector<long long>> dp3(n, vector<long long>(n, NEG));
		auto w2 = [&](int i, int j) -> long long { return i < j ? (long long)fruits[i][j] : 0LL; };
		auto w3 = [&](int i, int j) -> long long { return i > j ? (long long)fruits[i][j] : 0LL; };
		dp2[0][n - 1] = w2(0, n - 1);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (i == 0 && j == n - 1) continue;
				long long best = NEG;
				if (i > 0) {
					best = std::max(best, dp2[i - 1][j]);
					if (j > 0) best = std::max(best, dp2[i - 1][j - 1]);
					if (j + 1 < n) best = std::max(best, dp2[i - 1][j + 1]);
				}
				dp2[i][j] = best == NEG ? NEG : best + w2(i, j);
			}
		}
		dp3[n - 1][0] = w3(n - 1, 0);
		for (int j = 0; j < n; ++j) {
			for (int i = 0; i < n; ++i) {
				if (i == n - 1 && j == 0) continue;
				long long best = NEG;
				if (j > 0) {
					best = std::max(best, dp3[i][j - 1]);
					if (i > 0) best = std::max(best, dp3[i - 1][j - 1]);
					if (i + 1 < n) best = std::max(best, dp3[i + 1][j - 1]);
				}
				dp3[i][j] = best == NEG ? NEG : best + w3(i, j);
			}
		}
		long long res = diag + dp2[n - 1][n - 1] + dp3[n - 1][n - 1];
		return (int)res;
	}
};