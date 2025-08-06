class Solution {
public:
    vector<int> findOriginalArray(vector<int>& changed) {
        if (changed.size() % 2 != 0) return {};
        sort(changed.begin(), changed.end());
        unordered_map<int, int> count;
        for (int num : changed) {
            count[num]++;
        }
        vector<int> result;
        for (int num : changed) {
            if (count[num] == 0) continue;
            if (count[num * 2] == 0) return {};
            result.push_back(num);
            count[num]--;
            count[num * 2]--;
        }
        return result;
    }
}; 