class Solution {
public:
    int numWays(string s) {
        const int MOD = 1e9 + 7;
        int n = s.length();
        int totalOnes = 0;
        for (char c : s) {
            if (c == '1') totalOnes++;
        }
        if (totalOnes % 3 != 0) return 0;
        if (totalOnes == 0) {
            long long ways = 0;
            for (int i = 1; i < n - 1; ++i) {
                for (int j = i + 1; j < n; ++j) {
                    ways++;
                }
            }
            return ways % MOD;
        }
        int target = totalOnes / 3;
        vector<int> ones;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '1') ones.push_back(i);
        }
        long long first = 0, second = 0;
        int count = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '1') {
                count++;
                if (count == target) {
                    int j = i + 1;
                    while (j < n && s[j] == '0') j++;
                    first = j - i;
                }
                if (count == 2 * target) {
                    int j = i + 1;
                    while (j < n && s[j] == '0') j++;
                    second = j - i;
                    break;
                }
            }
        }
        return (first * second) % MOD;
    }
}; 