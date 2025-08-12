class Solution {
public:
    int maxDifference(std::string s) {
        int cnt[26] = {0};
        for (char c : s) cnt[c - 'a']++;
        int ans = -1000000;
        for (int i = 0; i < 26; ++i) {
            if (cnt[i] % 2 == 1) {
                for (int j = 0; j < 26; ++j) {
                    if (cnt[j] > 0 && cnt[j] % 2 == 0) {
                        int diff = cnt[i] - cnt[j];
                        if (diff > ans) ans = diff;
                    }
                }
            }
        }
        return ans;
    }
};