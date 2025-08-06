class Solution {
public:
    vector<int> lastVisitedIntegers(vector<int>& nums) {
        vector<int> seen;
        vector<int> ans;
        int consecutive = 0;
        for (int num : nums) {
            if (num == -1) {
                consecutive++;
                if (consecutive <= seen.size()) {
                    ans.push_back(seen[consecutive - 1]);
                } else {
                    ans.push_back(-1);
                }
            } else {
                seen.insert(seen.begin(), num);
                consecutive = 0;
            }
        }
        return ans;
    }
}; 