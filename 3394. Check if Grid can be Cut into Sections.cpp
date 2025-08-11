class Solution {
    static bool hasTwoGaps(std::vector<std::pair<int, int>>& intervals) {
        if (intervals.size() < 3) return false;
        std::sort(intervals.begin(), intervals.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            if (a.first != b.first) return a.first < b.first;
            return a.second < b.second;
        });
        int m = static_cast<int>(intervals.size());
        std::vector<int> prefixMax(m), suffixMin(m);
        prefixMax[0] = intervals[0].second;
        for (int i = 1; i < m; i++) prefixMax[i] = std::max(prefixMax[i - 1], intervals[i].second);
        suffixMin[m - 1] = intervals[m - 1].first;
        for (int i = m - 2; i >= 0; i--) suffixMin[i] = std::min(suffixMin[i + 1], intervals[i].first);
        int gaps = 0;
        for (int i = 0; i < m - 1; i++) {
            if (prefixMax[i] <= suffixMin[i + 1]) {
                gaps++;
                if (gaps >= 2) return true;
            }
        }
        return false;
    }
public:
    bool checkValidCuts(int n, std::vector<std::vector<int>>& rectangles) {
        std::vector<std::pair<int, int>> yIntervals;
        yIntervals.reserve(rectangles.size());
        for (const auto& r : rectangles) yIntervals.emplace_back(r[1], r[3]);
        if (hasTwoGaps(yIntervals)) return true;
        std::vector<std::pair<int, int>> xIntervals;
        xIntervals.reserve(rectangles.size());
        for (const auto& r : rectangles) xIntervals.emplace_back(r[0], r[2]);
        return hasTwoGaps(xIntervals);
    }
};