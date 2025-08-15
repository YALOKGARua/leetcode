#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>

using std::vector;
using std::unordered_map;

class Solution {
public:
	long long minCost(vector<int>& basket1, vector<int>& basket2) {
		int n = (int)basket1.size();
		unordered_map<int, long long> delta;
		int globalMin = INT_MAX;
		for (int v : basket1) {
			++delta[v];
			if (v < globalMin) globalMin = v;
		}
		for (int v : basket2) {
			--delta[v];
			if (v < globalMin) globalMin = v;
		}
		vector<int> fromA;
		vector<int> fromB;
		for (auto& kv : delta) {
			long long d = kv.second;
			if ((d & 1LL) != 0) return -1;
			if (d > 0) {
				int times = (int)(d / 2);
				fromA.insert(fromA.end(), times, kv.first);
			} else if (d < 0) {
				int times = (int)((-d) / 2);
				fromB.insert(fromB.end(), times, kv.first);
			}
		}
		if (fromA.empty()) return 0;
		std::sort(fromA.begin(), fromA.end());
		std::sort(fromB.begin(), fromB.end());
		long long answer = 0;
		int k = (int)fromA.size();
		for (int i = 0; i < k; ++i) {
			int x = fromA[i];
			int y = fromB[k - 1 - i];
			long long direct = std::min(x, y);
			long long viaMin = 2LL * (long long)globalMin;
			answer += std::min(direct, viaMin);
		}
		return answer;
	}
};