#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> maxSubsequence(vector<int>& nums, int k) {
        vector<pair<int, int>> arr;
        for (int i = 0; i < nums.size(); ++i) {
            arr.push_back({nums[i], i});
        }
        sort(arr.begin(), arr.end(), [](auto& a, auto& b) {
            return a.first > b.first;
        });
        arr.resize(k);
        sort(arr.begin(), arr.end(), [](auto& a, auto& b) {
            return a.second < b.second;
        });
        vector<int> res;
        for (auto& p : arr) res.push_back(p.first);
        return res;
    }
}; 