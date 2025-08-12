#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxFreeTime(int eventTime, int k, vector<int>& startTime, vector<int>& endTime) {
        int n = (int)startTime.size();
        vector<long long> gaps(n + 1);
        gaps[0] = (long long)startTime[0];
        for (int i = 1; i < n; ++i) gaps[i] = (long long)startTime[i] - endTime[i - 1];
        gaps[n] = (long long)eventTime - endTime[n - 1];
        int w = min(k + 1, n + 1);
        long long curr = 0, best = 0;
        for (int i = 0; i < w; ++i) curr += gaps[i];
        best = curr;
        for (int i = w; i <= n; ++i) {
            curr += gaps[i] - gaps[i - w];
            if (curr > best) best = curr;
        }
        return (int)best;
    }
};