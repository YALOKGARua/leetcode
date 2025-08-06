class Solution {
public:
    long long maximumPoints(vector<int>& enemyEnergies, int currentEnergy) {
        int n = enemyEnergies.size();
        if (n == 1) {
            return currentEnergy / enemyEnergies[0];
        }
        vector<int> sorted = enemyEnergies;
        sort(sorted.begin(), sorted.end());
        int minEnergy = sorted[0];
        if (currentEnergy < minEnergy) {
            return 0;
        }
        long long totalEnergy = 0;
        for (int i = 1; i < n; ++i) {
            totalEnergy += sorted[i];
        }
        long long energy = currentEnergy + totalEnergy;
        return energy / minEnergy;
    }
}; 