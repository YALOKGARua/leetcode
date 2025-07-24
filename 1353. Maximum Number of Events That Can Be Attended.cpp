#include <vector>
#include <queue>
#include <algorithm>
using std::vector;
using std::priority_queue;

class Solution {
public:
    int maxEvents(vector<vector<int>>& events) {
        std::sort(events.begin(), events.end());
        int n = events.size();
        priority_queue<int, vector<int>, std::greater<int>> pq;
        int res = 0, i = 0, day = 1;
        int maxDay = 0;
        for (const auto& e : events) maxDay = std::max(maxDay, e[1]);
        for (day = 1; day <= maxDay; ++day) {
            while (i < n && events[i][0] == day) {
                pq.push(events[i][1]);
                ++i;
            }
            while (!pq.empty() && pq.top() < day) pq.pop();
            if (!pq.empty()) {
                pq.pop();
                ++res;
            }
        }
        return res;
    }
}; 