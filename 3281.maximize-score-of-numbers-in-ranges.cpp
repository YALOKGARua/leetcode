class Solution {
private:
    bool canAchieve(vector<int>& start, int d, int target) {
        int n = start.size();
        vector<pair<int, int>> intervals;
        
        for (int i = 0; i < n; i++) {
            intervals.push_back({start[i], start[i] + d});
        }
        
        sort(intervals.begin(), intervals.end());
        
        vector<int> chosen(n);
        chosen[0] = intervals[0].first;
        
        for (int i = 1; i < n; i++) {
            int left = intervals[i].first;
            int right = intervals[i].second;
            
            bool found = false;
            
            for (int val = left; val <= right; val++) {
                bool valid = true;
                
                for (int j = 0; j < i; j++) {
                    if (abs(chosen[j] - val) < target) {
                        valid = false;
                        break;
                    }
                }
                
                if (valid) {
                    chosen[i] = val;
                    found = true;
                    break;
                }
            }
            
            if (!found) {
                return false;
            }
        }
        
        return true;
    }
    
public:
    int maxPossibleScore(vector<int>& start, int d) {
        int left = 0;
        int right = 1e9;
        int result = 0;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (canAchieve(start, d, mid)) {
                result = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result;
    }
}; 