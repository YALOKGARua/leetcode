class Solution {
public:
    int maxPathLength(vector<vector<int>>& coordinates, int k) {
        int n = coordinates.size();
        int targetX = coordinates[k][0];
        int targetY = coordinates[k][1];
        vector<pair<int, int>> points;
        for (int i = 0; i < n; ++i) {
            points.push_back({coordinates[i][0], coordinates[i][1]});
        }
        sort(points.begin(), points.end());
        int targetIndex = -1;
        for (int i = 0; i < n; ++i) {
            if (points[i].first == targetX && points[i].second == targetY) {
                targetIndex = i;
                break;
            }
        }
        int result = 1;
        for (int i = 0; i < n; ++i) {
            if (points[i].first <= targetX && points[i].second <= targetY) {
                for (int j = targetIndex; j < n; ++j) {
                    if (points[j].first >= targetX && points[j].second >= targetY) {
                        vector<pair<int, int>> path;
                        for (int p = 0; p < n; ++p) {
                            if (points[p].first >= points[i].first && points[p].first <= points[j].first &&
                                points[p].second >= points[i].second && points[p].second <= points[j].second) {
                                path.push_back(points[p]);
                            }
                        }
                        sort(path.begin(), path.end());
                        vector<int> dp(path.size(), 1);
                        bool hasTarget = false;
                        for (int p = 0; p < path.size(); ++p) {
                            if (path[p].first == targetX && path[p].second == targetY) {
                                hasTarget = true;
                            }
                            for (int q = 0; q < p; ++q) {
                                if (path[q].first < path[p].first && path[q].second < path[p].second) {
                                    dp[p] = max(dp[p], dp[q] + 1);
                                }
                            }
                        }
                        if (hasTarget) {
                            int maxLen = 0;
                            for (int len : dp) {
                                maxLen = max(maxLen, len);
                            }
                            result = max(result, maxLen);
                        }
                    }
                }
            }
        }
        return result;
    }
}; 