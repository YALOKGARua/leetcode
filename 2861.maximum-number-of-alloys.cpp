class Solution {
public:
    int maxNumberOfAlloys(int n, int k, int budget, vector<vector<int>>& composition, vector<int>& stock, vector<int>& cost) {
        int result = 0;
        for (int machine = 0; machine < k; ++machine) {
            long long maxPossible = LLONG_MAX;
            for (int metal = 0; metal < n; ++metal) {
                if (composition[machine][metal] > 0) {
                    maxPossible = min(maxPossible, (long long)stock[metal] / composition[machine][metal] + budget / cost[metal]);
                }
            }
            int left = 0, right = min((int)maxPossible, (int)1e9);
            while (left < right) {
                int mid = left + (right - left + 1) / 2;
                long long totalCost = 0;
                bool possible = true;
                for (int metal = 0; metal < n; ++metal) {
                    long long needed = (long long)composition[machine][metal] * mid;
                    if (needed > stock[metal]) {
                        totalCost += (needed - stock[metal]) * cost[metal];
                    }
                    if (totalCost > budget) {
                        possible = false;
                        break;
                    }
                }
                if (possible) {
                    left = mid;
                } else {
                    right = mid - 1;
                }
            }
            result = max(result, left);
        }
        return result;
    }
}; 