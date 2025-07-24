#include <string>
using std::string;

class Solution {
public:
    int possibleStringCount(string word) {
        int n = word.size();
        int res = 1;
        for (int i = 0; i < n;) {
            int j = i;
            while (j < n && word[j] == word[i]) ++j;
            int len = j - i;
            if (len > 1) res += len - 1;
            i = j;
        }
        return res;
    }
}; 