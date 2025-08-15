#include <vector>

using std::vector;

class Solution {
public:
	int findLatestStep(vector<int>& arr, int m) {
		int n = (int)arr.size();
		if (m == n) return n;
		vector<int> len(n + 2, 0);
		vector<int> cnt(n + 1, 0);
		int ans = -1;
		for (int step = 0; step < n; ++step) {
			int p = arr[step];
			int L = len[p - 1];
			int R = len[p + 1];
			int S = L + 1 + R;
			if (L) --cnt[L];
			if (R) --cnt[R];
			len[p - L] = S;
			len[p + R] = S;
			len[p] = S;
			++cnt[S];
			if (cnt[m] > 0) ans = step + 1;
		}
		return ans;
	}
};