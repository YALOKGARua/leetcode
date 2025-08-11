class Solution {
    static const int MOD = 1000000007;
    static long long modPow(long long base, long long exp) {
        long long result = 1 % MOD;
        base %= MOD;
        while (exp) {
            if (exp & 1) result = result * base % MOD;
            base = base * base % MOD;
            exp >>= 1;
        }
        return result;
    }
public:
    std::vector<int> productQueries(int n, std::vector<std::vector<int>>& queries) {
        std::vector<int> exponents;
        for (int bitPosition = 0; n > 0; bitPosition++) {
            if (n & 1) exponents.push_back(bitPosition);
            n >>= 1;
        }
        int length = static_cast<int>(exponents.size());
        std::vector<int> prefix(length + 1, 0);
        for (int i = 0; i < length; i++) prefix[i + 1] = prefix[i] + exponents[i];
        std::vector<int> answers;
        answers.reserve(queries.size());
        for (auto& query : queries) {
            int left = query[0], right = query[1];
            int exponentSum = prefix[right + 1] - prefix[left];
            answers.push_back(static_cast<int>(modPow(2, exponentSum)));
        }
        return answers;
    }
};