class Solution {
public:
    int countPairs(vector<int>& deliciousness) {
        const int MOD = 1e9 + 7;
        unordered_map<int, int> count;
        long long result = 0;
        for (int num : deliciousness) {
            for (int power = 1; power <= (1 << 21); power <<= 1) {
                int target = power - num;
                if (count.find(target) != count.end()) {
                    result = (result + count[target]) % MOD;
                }
            }
            count[num]++;
        }
        return (int)result;
    }
}; 