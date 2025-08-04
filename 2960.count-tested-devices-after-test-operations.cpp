class Solution {
public:
    int countTestedDevices(vector<int>& batteryPercentages) {
        int n = batteryPercentages.size();
        int testedCount = 0;
        
        for (int i = 0; i < n; i++) {
            if (batteryPercentages[i] > 0) {
                testedCount++;
                
                for (int j = i + 1; j < n; j++) {
                    batteryPercentages[j] = max(0, batteryPercentages[j] - 1);
                }
            }
        }
        
        return testedCount;
    }
}; 