#include <string>

using std::string;

class Solution {
public:
	string largestGoodInteger(string num) {
		int n = (int)num.size();
		int best = -1;
		for (int i = 0; i + 2 < n; ++i) if (num[i] == num[i + 1] && num[i] == num[i + 2]) {
			int d = num[i] - '0';
			if (d > best) best = d;
		}
		if (best < 0) return "";
		return string(3, char('0' + best));
	}
};