class Solution {
private:
    bool canConvertToZero(vector<int>& nums, vector<vector<int>>& queries, int removeCount) {
        int n = nums.size();
        vector<int> target = nums;
        
        vector<vector<int>> remainingQueries;
        for (int i = 0; i < queries.size() - removeCount; i++) {
            remainingQueries.push_back(queries[i]);
        }
        
        for (auto& query : remainingQueries) {
            int l = query[0], r = query[1];
            for (int i = l; i <= r; i++) {
                if (target[i] > 0) {
                    target[i]--;
                }
            }
        }
        
        for (int val : target) {
            if (val > 0) return false;
        }
        return true;
    }
    
    bool canConvertToZeroOptimal(vector<int>& nums, vector<vector<int>>& queries, int removeCount) {
        int n = nums.size();
        vector<int> target = nums;
        
        vector<vector<int>> remainingQueries;
        for (int i = 0; i < queries.size() - removeCount; i++) {
            remainingQueries.push_back(queries[i]);
        }
        
        for (auto& query : remainingQueries) {
            int l = query[0], r = query[1];
            for (int i = l; i <= r; i++) {
                if (target[i] > 0) {
                    target[i]--;
                }
            }
        }
        
        for (int val : target) {
            if (val > 0) return false;
        }
        return true;
    }
    
    bool canConvertToZero(vector<int>& nums, vector<vector<int>>& queries, int removeCount) {
        int n = nums.size();
        vector<int> target = nums;
        
        vector<vector<int>> remainingQueries;
        for (int i = 0; i < queries.size() - removeCount; i++) {
            remainingQueries.push_back(queries[i]);
        }
        
        for (auto& query : remainingQueries) {
            int l = query[0], r = query[1];
            for (int i = l; i <= r; i++) {
                if (target[i] > 0) {
                    target[i]--;
                }
            }
        }
        
        for (int val : target) {
            if (val > 0) return false;
        }
        return true;
    }
    
public:
    int maxRemoval(vector<int>& nums, vector<vector<int>>& queries) {
        int left = 0, right = queries.size();
        int result = -1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (canConvertToZero(nums, queries, mid)) {
                result = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result;
    }
}; 