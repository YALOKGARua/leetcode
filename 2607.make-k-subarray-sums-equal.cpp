class Solution {
public:
    long long makeSubKSumEqual(vector<int>& arr, int k) {
        int n = arr.size();
        int g = __gcd(n, k);
        long long result = 0;
        for (int i = 0; i < g; ++i) {
            vector<int> group;
            for (int j = i; j < n; j += g) {
                group.push_back(arr[j]);
            }
            sort(group.begin(), group.end());
            int median = group[group.size() / 2];
            for (int val : group) {
                result += abs(val - median);
            }
        }
        return result;
    }
}; 