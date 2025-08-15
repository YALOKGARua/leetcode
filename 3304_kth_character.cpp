class Solution {
public:
	char kthCharacter(int k) {
		int s = __builtin_popcount((unsigned int)(k - 1));
		return char('a' + (s % 26));
	}
};