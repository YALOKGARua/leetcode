#include <vector>

using std::vector;

class Solution {
public:
	char kthCharacter(long long k, vector<int>& operations) {
		long long r = k - 1;
		long long add = 0;
		int t = (int)operations.size();
		for (int i = 0; i < t; ++i) {
			if (operations[i] == 1) {
				bool second = false;
				if (i < 62) second = ((r >> i) & 1LL);
				if (second) ++add;
			}
		}
		return char('a' + (int)(add % 26));
	}
};