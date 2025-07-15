#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minimizeMax(vector<int>& nums, int p) {
        sort(nums.begin(), nums.end());
        int left = 0, right = nums.back() - nums.front();
        auto can = [&](int maxDiff) {
            int cnt = 0;
            for (int i = 1; i < nums.size(); ) {
                if (nums[i] - nums[i-1] <= maxDiff) {
                    ++cnt;
                    i += 2;
                } else {
                    ++i;
                }
            }
            return cnt >= p;
        };
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (can(mid)) right = mid;
            else left = mid + 1;
        }
        return left;
    }
};