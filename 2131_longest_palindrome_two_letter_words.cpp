#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using std::vector;
using std::string;
using std::unordered_map;

class Solution {
public:
	int longestPalindrome(vector<string>& words) {
		unordered_map<string, int> cnt;
		for (auto& w : words) ++cnt[w];
		long long ans = 0;
		bool center = false;
		for (auto& kv : cnt) {
			const string& w = kv.first;
			int c = kv.second;
			if (w[0] == w[1]) {
				ans += (c / 2) * 4;
				if (c % 2 == 1) center = true;
			} else if (w[0] < w[1]) {
				string r; r.push_back(w[1]); r.push_back(w[0]);
				auto it = cnt.find(r);
				if (it != cnt.end()) ans += 4LL * std::min(c, it->second);
			}
		}
		if (center) ans += 2;
		return (int)ans;
	}
};