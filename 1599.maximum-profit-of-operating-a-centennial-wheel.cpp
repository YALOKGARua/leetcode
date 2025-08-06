class Solution {
public:
    int minOperationsMaxProfit(vector<int>& customers, int boardingCost, int runningCost) {
        int waiting = 0;
        int boarded = 0;
        int rotations = 0;
        int maxProfit = 0;
        int result = -1;
        int n = customers.size();
        for (int i = 0; i < n; ++i) {
            waiting += customers[i];
            int board = min(4, waiting);
            boarded += board;
            waiting -= board;
            rotations++;
            int profit = boarded * boardingCost - rotations * runningCost;
            if (profit > maxProfit) {
                maxProfit = profit;
                result = rotations;
            }
        }
        while (waiting > 0) {
            int board = min(4, waiting);
            boarded += board;
            waiting -= board;
            rotations++;
            int profit = boarded * boardingCost - rotations * runningCost;
            if (profit > maxProfit) {
                maxProfit = profit;
                result = rotations;
            }
        }
        return result;
    }
}; 