#include <string>
#include <vector>
#include <algorithm>
#include <climits>
using std::string;
using std::vector;

class Solution {
public:
    int minimumDeletions(string word, int k) {
        vector<int> freq(26, 0);
        for (char c : word) freq[c - 'a']++;
        vector<int> counts;
        for (int f : freq) if (f > 0) counts.push_back(f);
        int res = INT_MAX;
        std::sort(counts.begin(), counts.end());
        for (int i = 0; i < counts.size(); ++i) {
            int x = counts[i];
            int del = 0;
            for (int y : counts) {
                if (y < x) del += y;
                else if (y > x + k) del += y - (x + k);
            }
            res = std::min(res, del);
        }
        return res;
    }
}; 