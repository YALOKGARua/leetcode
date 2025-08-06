class Solution {
    public:
        int minimumSeconds(vector<int>& nums) {
            int n = nums.size();
            unordered_map<int, vector<int>> positions;
            for (int i = 0; i < n; ++i) {
                positions[nums[i]].push_back(i);
            }
            int result = INT_MAX;
            for (auto& [value, pos] : positions) {
                if (pos.size() == n) return 0;
                int maxDist = 0;
                for (int i = 0; i < pos.size(); ++i) {
                    int next = (i + 1) % pos.size();
                    int dist = (pos[next] - pos[i] + n) % n;
                    maxDist = max(maxDist, dist / 2);
                }
                result = min(result, maxDist);
            }
            return result;
        }
    }; 