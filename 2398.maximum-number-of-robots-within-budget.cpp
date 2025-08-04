#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maximumRobots(vector<int>& chargeTimes, vector<int>& runningCosts, long long budget) {
        int n = chargeTimes.size();
        int left = 0;
        long long runningSum = 0;
        deque<int> dq;
        int maxRobots = 0;
        
        for (int right = 0; right < n; right++) {
            runningSum += runningCosts[right];
            
            while (!dq.empty() && chargeTimes[dq.back()] <= chargeTimes[right]) {
                dq.pop_back();
            }
            dq.push_back(right);
            
            while (left <= right && chargeTimes[dq.front()] + (right - left + 1) * runningSum > budget) {
                runningSum -= runningCosts[left];
                
                if (dq.front() == left) {
                    dq.pop_front();
                }
                left++;
            }
            
            maxRobots = max(maxRobots, right - left + 1);
        }
        
        return maxRobots;
    }
}; 