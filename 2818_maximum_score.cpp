#include <vector>
#include <stack>
#include <algorithm>

using std::vector;

class Solution {
public:
	int maximumScore(vector<int>& nums, int k) {
		static const int MOD = 1000000007;
		int n = (int)nums.size();
		int mx = *std::max_element(nums.begin(), nums.end());
		vector<int> spf(mx + 1);
		for (int i = 2; i <= mx; ++i) {
			if (spf[i] == 0) {
				spf[i] = i;
				if ((long long)i * i <= mx) for (long long j = 1LL * i * i; j <= mx; j += i) if (spf[(int)j] == 0) spf[(int)j] = i;
			}
		}
		auto primeScore = [&](int x) {
			int c = 0;
			while (x > 1) {
				int p = spf[x];
				++c;
				while (x % p == 0) x /= p;
			}
			return c;
		};
		vector<int> score(n);
		for (int i = 0; i < n; ++i) score[i] = primeScore(nums[i]);
		vector<int> left(n), right(n);
		std::stack<int> st;
		for (int i = 0; i < n; ++i) {
			while (!st.empty() && score[st.top()] < score[i]) st.pop();
			int j = st.empty() ? -1 : st.top();
			left[i] = i - j;
			st.push(i);
		}
		while (!st.empty()) st.pop();
		for (int i = n - 1; i >= 0; --i) {
			while (!st.empty() && score[st.top()] <= score[i]) st.pop();
			int j = st.empty() ? n : st.top();
			right[i] = j - i;
			st.push(i);
		}
		vector<int> idx(n);
		for (int i = 0; i < n; ++i) idx[i] = i;
		std::sort(idx.begin(), idx.end(), [&](int a, int b){ return nums[a] > nums[b]; });
		auto modPow = [&](long long a, long long e) {
			long long r = 1 % MOD;
			a %= MOD;
			while (e > 0) {
				if (e & 1) r = (r * a) % MOD;
				a = (a * a) % MOD;
				e >>= 1;
			}
			return (int)r;
		};
		long long ans = 1;
		long long need = k;
		for (int i : idx) {
			long long cnt = (long long)left[i] * (long long)right[i];
			if (cnt <= 0) continue;
			long long take = std::min(cnt, need);
			ans = (ans * modPow(nums[i], take)) % MOD;
			need -= take;
			if (need == 0) break;
		}
		return (int)ans;
	}
};


