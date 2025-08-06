class Solution {
public:
    int specialTriplets(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        unordered_map<int, int> left, right;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            right[nums[i]]++;
        }
        long long ans = 0;
        for (int j = 0; j < n; ++j) {
            right[nums[j]]--;
            if (nums[j] * 2 <= 100000) {
                long long cnt_left = left[nums[j] * 2];
                long long cnt_right = right[nums[j] * 2];
                ans = (ans + cnt_left * cnt_right) % MOD;
            }
            left[nums[j]]++;
        }
        return (int)ans;
    }
}; 