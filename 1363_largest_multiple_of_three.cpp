#include <vector>
#include <string>

using std::vector;
using std::string;

class Solution {
public:
	string largestMultipleOfThree(vector<int>& digits) {
		int cnt[10] = {0};
		int sum = 0;
		for (int d : digits) { ++cnt[d]; sum += d; }
		auto removeOneFrom = [&](const int* group) {
			for (int i = 0; i < 3; ++i) if (cnt[group[i]] > 0) { --cnt[group[i]]; return true; }
			return false;
		};
		auto removeTwoFrom = [&](const int* group) {
			int need = 2;
			int total = cnt[group[0]] + cnt[group[1]] + cnt[group[2]];
			if (total < 2) return false;
			for (int i = 0; i < 3 && need; ++i) {
				int take = cnt[group[i]] < need ? cnt[group[i]] : need;
				cnt[group[i]] -= take;
				need -= take;
			}
			return need == 0;
		};
		const int mod1[3] = {1, 4, 7};
		const int mod2[3] = {2, 5, 8};
		int r = sum % 3;
		if (r == 1) {
			if (!removeOneFrom(mod1)) {
				if (!removeTwoFrom(mod2)) return "";
			}
		} else if (r == 2) {
			if (!removeOneFrom(mod2)) {
				if (!removeTwoFrom(mod1)) return "";
			}
		}
		string res;
		res.reserve(digits.size());
		for (int d = 9; d >= 0; --d) while (cnt[d]--) res.push_back(char('0' + d));
		if (res.empty()) return "";
		if (res[0] == '0') return "0";
		return res;
	}
};