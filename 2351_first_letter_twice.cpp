#include <string>
#include <vector>

using std::string;
using std::vector;

class Solution {
public:
	char repeatedCharacter(string s) {
		vector<int> seen(26, 0);
		for (char c : s) {
			int i = c - 'a';
			if (seen[i]) return c;
			seen[i] = 1;
		}
		return 'a';
	}
};