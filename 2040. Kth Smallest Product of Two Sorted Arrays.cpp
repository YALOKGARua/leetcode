#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    long long kthSmallestProduct(vector<int>& nums1, vector<int>& nums2, long long k) {
        long long left = -1e10, right = 1e10;
        while (left < right) {
            long long mid = left + (right - left) / 2;
            if (countLE(nums1, nums2, mid) < k) left = mid + 1;
            else right = mid;
        }
        return left;
    }
    long long countLE(const vector<int>& nums1, const vector<int>& nums2, long long x) {
        long long cnt = 0, n2 = nums2.size();
        for (int a : nums1) {
            if (a == 0) {
                if (x >= 0) cnt += n2;
            } else if (a > 0) {
                int l = 0, r = n2;
                while (l < r) {
                    int m = (l + r) / 2;
                    if ((long long)a * nums2[m] <= x) l = m + 1;
                    else r = m;
                }
                cnt += l;
            } else {
                int l = 0, r = n2;
                while (l < r) {
                    int m = (l + r) / 2;
                    if ((long long)a * nums2[m] <= x) r = m;
                    else l = m + 1;
                }
                cnt += n2 - l;
            }
        }
        return cnt;
    }
};
