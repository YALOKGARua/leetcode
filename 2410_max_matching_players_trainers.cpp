#include <vector>
#include <algorithm>

using std::vector;

class Solution {
public:
	int matchPlayersAndTrainers(vector<int>& players, vector<int>& trainers) {
		std::sort(players.begin(), players.end());
		std::sort(trainers.begin(), trainers.end());
		int i = 0, j = 0, n = (int)players.size(), m = (int)trainers.size();
		int ans = 0;
		while (i < n && j < m) {
			if (players[i] <= trainers[j]) { ++ans; ++i; ++j; }
			else { ++j; }
		}
		return ans;
	}
};