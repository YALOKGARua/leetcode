#include <vector>
#include <algorithm>

using std::vector;

class Solution {
public:
	int maxCoins(vector<int>& piles) {
		std::sort(piles.begin(), piles.end());
		int n = (int)piles.size();
		int i = 0, j = n - 1;
		long long ans = 0;
		while (i < j) {
			--j;
			ans += piles[j];
			--j;
			++i;
		}
		return (int)ans;
	}
};