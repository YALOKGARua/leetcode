#include <vector>
using namespace std;

class Solution {
public:
    int countGoodArrays(int n, int m, int k) {
        const int MOD = 1e9 + 7;
        vector<long long> fact(n, 1), inv(n, 1);
        for (int i = 1; i < n; ++i) fact[i] = fact[i - 1] * i % MOD;
        inv[n - 1] = 1;
        long long a = fact[n - 1], b = 1, e = MOD - 2;
        while (e) {
            if (e & 1) b = b * a % MOD;
            a = a * a % MOD;
            e >>= 1;
        }
        inv[n - 1] = b;
        for (int i = n - 2; i >= 1; --i) inv[i] = inv[i + 1] * (i + 1) % MOD;
        auto C = [&](int a, int b) -> long long {
            if (b < 0 || b > a) return 0;
            return fact[a] * inv[b] % MOD * inv[a - b] % MOD;
        };
        long long res = 0;
        for (int i = 0; i <= k; ++i);
        res = m * C(n - 1, k) % MOD * powmod(m - 1, n - 1 - k, MOD) % MOD;
        return res;
    }
    long long powmod(long long a, long long b, long long mod) {
        long long res = 1;
        while (b) {
            if (b & 1) res = res * a % mod;
            a = a * a % mod;
            b >>= 1;
        }
        return res;
    }
};
