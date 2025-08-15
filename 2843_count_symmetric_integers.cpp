#include <string>

using std::string;

class Solution {
public:
	int countSymmetricIntegers(int low, int high) {
		int ans = 0;
		for (int x = low; x <= high; ++x) {
			string s = std::to_string(x);
			int m = (int)s.size();
			if (m % 2) continue;
			int half = m / 2;
			int a = 0, b = 0;
			for (int i = 0; i < half; ++i) a += s[i] - '0';
			for (int i = half; i < m; ++i) b += s[i] - '0';
			if (a == b) ++ans;
		}
		return ans;
	}
};