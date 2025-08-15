#include <string>
#include <vector>

using std::string;
using std::vector;

class Solution {
public:
	string robotWithString(string s) {
		vector<int> cnt(26, 0);
		for (char c : s) ++cnt[c - 'a'];
		int mn = 0;
		while (mn < 26 && cnt[mn] == 0) ++mn;
		string t, p;
		p.reserve(s.size());
		for (char c : s) {
			--cnt[c - 'a'];
			while (mn < 26 && cnt[mn] == 0) ++mn;
			t.push_back(c);
			while (!t.empty() && (mn == 26 || t.back() <= char('a' + mn))) {
				p.push_back(t.back());
				t.pop_back();
			}
		}
		while (!t.empty()) {
			p.push_back(t.back());
			t.pop_back();
		}
		return p;
	}
};