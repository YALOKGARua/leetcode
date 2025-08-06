class Solution {
    public:
        long long minimumMoves(vector<int>& nums, int k, int maxChanges) {
            vector<int> ones;
            int n = nums.size();
            for (int i = 0; i < n; ++i) {
                if (nums[i] == 1) ones.push_back(i);
            }
            long long res = LLONG_MAX;
            int totalOnes = ones.size();
            for (int usedChanges = 0; usedChanges <= min(k, maxChanges); ++usedChanges) {
                int need = k - usedChanges;
                if (need == 0) {
                    res = min(res, 2LL * usedChanges);
                    continue;
                }
                if (need > totalOnes) continue;
                vector<long long> prefix(totalOnes + 1, 0);
                for (int i = 0; i < totalOnes; ++i) {
                    prefix[i + 1] = prefix[i] + ones[i];
                }
                for (int l = 0; l + need <= totalOnes; ++l) {
                    int r = l + need - 1;
                    int m = l + need / 2;
                    long long left = ones[m] * (m - l) - (prefix[m] - prefix[l]);
                    long long right = (prefix[r + 1] - prefix[m + 1]) - ones[m] * (r - m);
                    long long moves = left + right + need + 2LL * usedChanges;
                    res = min(res, moves);
                }
            }
            return res;
        }
    }; 