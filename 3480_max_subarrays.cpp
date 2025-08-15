#include <vector>
#include <map>
#include <algorithm>

using std::vector;
using std::map;

class Solution {
public:
	long long maxSubarrays(int n, vector<vector<int>>& conflictingPairs) {
		int m = (int)conflictingPairs.size();
		vector<vector<std::pair<int,int>>> byLeft(n + 2);
		for (int id = 0; id < m; ++id) {
			int a = conflictingPairs[id][0];
			int b = conflictingPairs[id][1];
			if (a > b) std::swap(a, b);
			byLeft[a].push_back({id, b});
		}
		vector<int> rightCount(n + 2, 0);
		vector<int> uniqueIdByRight(n + 2, -1);
		map<int, int> rightFrequency;
		long long base = 0;
		vector<long long> delta(m, 0);
		for (int L = n; L >= 1; --L) {
			for (auto& pr : byLeft[L]) {
				int id = pr.first;
				int r = pr.second;
				if (rightCount[r] == 0) uniqueIdByRight[r] = id;
				++rightCount[r];
				++rightFrequency[r];
			}
			if (rightFrequency.empty()) {
				base += (long long)(n + 1 - L);
				continue;
			}
			auto it = rightFrequency.begin();
			int minR = it->first;
			base += (long long)(minR - L);
			if (it->second == 1) {
				int nextR = n + 1;
				auto it2 = it;
				++it2;
				if (it2 != rightFrequency.end()) nextR = it2->first;
				int idMin = uniqueIdByRight[minR];
				delta[idMin] += (long long)(nextR - minR);
			}
		}
		long long best = 0;
		for (long long v : delta) if (v > best) best = v;
		return base + best;
	}
};