#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    string clearStars(string s) {
        vector<pair<char, int>> stk;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '*') {
                int idx = -1;
                for (int j = stk.size() - 1; j >= 0; --j) {
                    if (stk[j].second < i && (idx == -1 || stk[j].first < stk[idx].first)) idx = j;
                }
                if (idx != -1) stk.erase(stk.begin() + idx);
            } else {
                stk.push_back({s[i], i});
            }
        }
        string res;
        for (auto& p : stk) res += p.first;
        return res;
    }
};