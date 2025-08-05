#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
public:
    long long minimumDifference(vector<int>& nums) {
        int n = nums.size() / 3;
        int N = nums.size();
        vector<long long> left(N, 0), right(N, 0);
        priority_queue<int> maxHeap;
        long long sum = 0;
        for (int i = 0; i < N; ++i) {
            sum += nums[i];
            maxHeap.push(nums[i]);
            if (maxHeap.size() > n) {
                sum -= maxHeap.top();
                maxHeap.pop();
            }
            if (i >= n-1) left[i] = sum;
        }
        priority_queue<int, vector<int>, greater<int>> minHeap;
        sum = 0;
        for (int i = N-1; i >= 0; --i) {
            sum += nums[i];
            minHeap.push(nums[i]);
            if (minHeap.size() > n) {
                sum -= minHeap.top();
                minHeap.pop();
            }
            if (i <= 2*n) right[i] = sum;
        }
        long long res = LLONG_MAX;
        for (int i = n-1; i < 2*n; ++i) {
            res = min(res, left[i] - right[i+1]);
        }
        return res;
    }
}; 