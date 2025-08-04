class Solution {
public:
    long long minCost(vector<int>& basket1, vector<int>& basket2) {
        unordered_map<int, int> freq1, freq2;
        
        for (int fruit : basket1) freq1[fruit]++;
        for (int fruit : basket2) freq2[fruit]++;
        
        vector<int> excess1, excess2;
        int minElement = INT_MAX;
        
        for (int fruit : basket1) {
            minElement = min(minElement, fruit);
        }
        for (int fruit : basket2) {
            minElement = min(minElement, fruit);
        }
        
        for (auto& [fruit, count] : freq1) {
            int diff = count - freq2[fruit];
            if (diff % 2 != 0) return -1;
            if (diff > 0) {
                for (int i = 0; i < diff / 2; i++) {
                    excess1.push_back(fruit);
                }
            }
        }
        
        for (auto& [fruit, count] : freq2) {
            if (freq1.find(fruit) == freq1.end()) {
                if (count % 2 != 0) return -1;
                for (int i = 0; i < count / 2; i++) {
                    excess2.push_back(fruit);
                }
            } else {
                int diff = freq2[fruit] - freq1[fruit];
                if (diff > 0) {
                    for (int i = 0; i < diff / 2; i++) {
                        excess2.push_back(fruit);
                    }
                }
            }
        }
        
        sort(excess1.begin(), excess1.end());
        sort(excess2.begin(), excess2.end());
        
        long long totalCost = 0;
        int n = excess1.size();
        
        for (int i = 0; i < n; i++) {
            totalCost += min(excess1[i], excess2[i]);
        }
        
        if (n > 0) {
            long long directCost = totalCost;
            long long indirectCost = 0;
            
            for (int i = 0; i < n; i++) {
                indirectCost += min(excess1[i], 2 * minElement) + min(excess2[i], 2 * minElement);
            }
            
            totalCost = min(directCost, indirectCost);
        }
        
        return totalCost;
    }
}; 