class Solution {
    static long long minSteps(int L, int R, int S) {
        if (R <= S) return S - L;
        if (L >= S) return R - S;
        long long leftCost = 2LL * (S - L) + (R - S);
        long long rightCost = 2LL * (R - S) + (S - L);
        return std::min(leftCost, rightCost);
    }
public:
    int maxTotalFruits(std::vector<std::vector<int>>& fruits, int startPos, int k) {
        int n = static_cast<int>(fruits.size());
        std::vector<int> positions(n), amounts(n);
        for (int i = 0; i < n; i++) {
            positions[i] = fruits[i][0];
            amounts[i] = fruits[i][1];
        }
        std::vector<long long> prefix(n + 1, 0);
        for (int i = 0; i < n; i++) prefix[i + 1] = prefix[i] + amounts[i];
        long long best = 0;
        int left = 0;
        for (int right = 0; right < n; right++) {
            while (left <= right && minSteps(positions[left], positions[right], startPos) > k) left++;
            if (left <= right) best = std::max(best, prefix[right + 1] - prefix[left]);
        }
        return static_cast<int>(best);
    }
};