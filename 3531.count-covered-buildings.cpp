class Solution {
public:
    int countCoveredBuildings(int n, vector<vector<int>>& buildings) {
        set<pair<int, int>> buildingSet;
        for (auto& building : buildings) {
            buildingSet.insert({building[0], building[1]});
        }
        int count = 0;
        for (auto& building : buildings) {
            int x = building[0], y = building[1];
            bool hasLeft = buildingSet.count({x - 1, y}) > 0;
            bool hasRight = buildingSet.count({x + 1, y}) > 0;
            bool hasAbove = buildingSet.count({x, y + 1}) > 0;
            bool hasBelow = buildingSet.count({x, y - 1}) > 0;
            if (hasLeft && hasRight && hasAbove && hasBelow) {
                count++;
            }
        }
        return count;
    }
}; 