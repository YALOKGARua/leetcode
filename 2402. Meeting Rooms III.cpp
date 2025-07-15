#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        sort(meetings.begin(), meetings.end());
        vector<long long> roomEnd(n, 0);
        vector<int> count(n, 0);
        priority_queue<int, vector<int>, greater<int>> freeRooms;
        for (int i = 0; i < n; ++i) freeRooms.push(i);
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> busyRooms;
        for (auto& m : meetings) {
            long long start = m[0], end = m[1];
            while (!busyRooms.empty() && busyRooms.top().first <= start) {
                freeRooms.push(busyRooms.top().second);
                busyRooms.pop();
            }
            if (!freeRooms.empty()) {
                int room = freeRooms.top(); freeRooms.pop();
                roomEnd[room] = end;
                count[room]++;
                busyRooms.emplace(end, room);
            } else {
                auto [freeTime, room] = busyRooms.top(); busyRooms.pop();
                roomEnd[room] = freeTime + (end - start);
                count[room]++;
                busyRooms.emplace(roomEnd[room], room);
            }
        }
        int maxCount = 0, res = 0;
        for (int i = 0; i < n; ++i) {
            if (count[i] > maxCount) {
                maxCount = count[i];
                res = i;
            }
        }
        return res;
    }
};
