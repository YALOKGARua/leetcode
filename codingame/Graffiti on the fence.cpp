#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int l, n;
    cin >> l >> n;
    cin.ignore();
    
    vector<pair<int, int>> painted;
    for (int i = 0; i < n; i++) {
        int st, ed;
        cin >> st >> ed;
        cin.ignore();
        painted.push_back({st, ed});
    }
    
    if (n == 0) {
        cout << "0 " << l << endl;
        return 0;
    }
    
    sort(painted.begin(), painted.end());
    
    vector<pair<int, int>> merged;
    int currentStart = painted[0].first;
    int currentEnd = painted[0].second;
    
    for (int i = 1; i < painted.size(); i++) {
        if (painted[i].first <= currentEnd) {
            currentEnd = max(currentEnd, painted[i].second);
        } else {
            merged.push_back({currentStart, currentEnd});
            currentStart = painted[i].first;
            currentEnd = painted[i].second;
        }
    }
    merged.push_back({currentStart, currentEnd});
    
    vector<pair<int, int>> unpainted;
    
    if (merged[0].first > 0) {
        unpainted.push_back({0, merged[0].first});
    }
    
    for (int i = 0; i < merged.size() - 1; i++) {
        if (merged[i].second < merged[i + 1].first) {
            unpainted.push_back({merged[i].second, merged[i + 1].first});
        }
    }
    
    if (merged.back().second < l) {
        unpainted.push_back({merged.back().second, l});
    }
    
    if (unpainted.empty()) {
        cout << "All painted" << endl;
    } else {
        for (const auto& segment : unpainted) {
            cout << segment.first << " " << segment.second << endl;
        }
    }
    
    return 0;
}
