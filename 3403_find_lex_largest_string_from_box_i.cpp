#include <string>

using std::string;

class Solution {
public:
	string answerString(string word, int numFriends) {
		int n = (int)word.size();
		auto greaterSub = [&](int i1, int len1, int i2, int len2) {
			int m = len1 < len2 ? len1 : len2;
			int k = 0;
			while (k < m && word[i1 + k] == word[i2 + k]) ++k;
			if (k < m) return word[i1 + k] > word[i2 + k];
			return len1 > len2;
		};
		if (numFriends == 1) return word;
		if (numFriends == 2) {
			int bestStart = 0, bestLen = n - 1;
			for (int i = 1; i < n; ++i) {
				int len = n - i;
				if (greaterSub(i, len, bestStart, bestLen)) {
					bestStart = i; bestLen = len;
				}
			}
			return word.substr(bestStart, bestLen);
		}
		int L = n - numFriends + 1;
		int bestStart = 0, bestLen = L;
		for (int i = 1; i < n; ++i) {
			int len = L < (n - i) ? L : (n - i);
			if (len <= 0) break;
			if (greaterSub(i, len, bestStart, bestLen)) {
				bestStart = i; bestLen = len;
			}
		}
		return word.substr(bestStart, bestLen);
	}
};