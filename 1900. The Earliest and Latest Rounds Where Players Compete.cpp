class Solution {
    using P = std::pair<int, int>;
    std::unordered_map<long long, P> memo;
    static long long kkey(int n, int a, int b) {
        if (a > b) std::swap(a, b);
        return (static_cast<long long>(n) << 20) | (static_cast<long long>(a) << 10) | b;
    }
    P dfs(int n, int a, int b) {
        if (a + b == n + 1) return {1, 1};
        long long kk = kkey(n, a, b);
        auto it = memo.find(kk);
        if (it != memo.end()) return it->second;
        int pairs = n / 2;
        bool hasMid = (n & 1) != 0;
        int mid = pairs + 1;
        std::vector<std::vector<char>> dp(pairs + 2, std::vector<char>(pairs + 2, 0));
        int baseL = 0, baseM = 0;
        if (hasMid) {
            if (mid < a) baseL = 1; else if (mid > a && mid < b) baseM = 1;
        }
        dp[baseL][baseM] = 1;
        for (int i = 1; i <= pairs; i++) {
            int left = i;
            int right = n + 1 - i;
            bool hasA = (left == a || right == a);
            bool hasB = (left == b || right == b);
            std::vector<std::vector<char>> ndp(pairs + 2, std::vector<char>(pairs + 2, 0));
            for (int l = 0; l <= pairs + 1; l++) {
                for (int m = 0; m <= pairs + 1; m++) {
                    if (!dp[l][m]) continue;
                    if (hasA || hasB) {
                        ndp[l][m] = 1;
                    } else {
                        int nl = l + (left < a ? 1 : 0);
                        int nm = m + ((left > a && left < b) ? 1 : 0);
                        ndp[nl][nm] = 1;
                        nl = l + (right < a ? 1 : 0);
                        nm = m + ((right > a && right < b) ? 1 : 0);
                        ndp[nl][nm] = 1;
                    }
                }
            }
            dp.swap(ndp);
        }
        int nextN = pairs + (hasMid ? 1 : 0);
        int bestMin = 1e9;
        int bestMax = -1e9;
        std::unordered_set<int> seen;
        for (int l = 0; l <= pairs + 1; l++) {
            for (int m = 0; m <= pairs + 1; m++) {
                if (!dp[l][m]) continue;
                int na = l + 1;
                int nb = l + 2 + m;
                if (na < 1 || nb > nextN || na >= nb) {
                    if (na < 1 || na > nextN) continue;
                    if (nb < 1 || nb > nextN) continue;
                    if (na >= nb) {
                        if (na + nb != nextN + 1) continue;
                    }
                }
                int enc = (na << 8) | nb;
                if (!seen.insert(enc).second) continue;
                P sub = dfs(nextN, na, nb);
                bestMin = std::min(bestMin, sub.first + 1);
                bestMax = std::max(bestMax, sub.second + 1);
            }
        }
        P res = {bestMin, bestMax};
        memo[kk] = res;
        return res;
    }
public:
    std::vector<int> earliestAndLatest(int n, int firstPlayer, int secondPlayer) {
        if (firstPlayer > secondPlayer) std::swap(firstPlayer, secondPlayer);
        P ans = dfs(n, firstPlayer, secondPlayer);
        return {ans.first, ans.second};
    }
};