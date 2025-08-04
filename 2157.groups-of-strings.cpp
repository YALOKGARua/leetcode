class Solution {
private:
    vector<int> parent, rank;
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return;
        
        if (rank[px] < rank[py]) {
            parent[px] = py;
        } else if (rank[px] > rank[py]) {
            parent[py] = px;
        } else {
            parent[py] = px;
            rank[px]++;
        }
    }
    
    bool areConnected(const string& s1, const string& s2) {
        int len1 = s1.length(), len2 = s2.length();
        
        if (abs(len1 - len2) > 1) return false;
        
        if (len1 == len2) {
            int diff = 0;
            for (int i = 0; i < len1; i++) {
                if (s1[i] != s2[i]) diff++;
                if (diff > 1) return false;
            }
            return true;
        }
        
        if (len1 < len2) {
            return canTransform(s1, s2);
        } else {
            return canTransform(s2, s1);
        }
    }
    
    bool canTransform(const string& shorter, const string& longer) {
        int i = 0, j = 0;
        int skip = 0;
        
        while (i < shorter.length() && j < longer.length()) {
            if (shorter[i] == longer[j]) {
                i++;
                j++;
            } else {
                skip++;
                j++;
                if (skip > 1) return false;
            }
        }
        
        return i == shorter.length() && skip == 1 && j == longer.length();
    }
    
public:
    vector<int> groupStrings(vector<string>& words) {
        int n = words.size();
        parent.resize(n);
        rank.resize(n, 0);
        
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (areConnected(words[i], words[j])) {
                    unite(i, j);
                }
            }
        }
        
        unordered_map<int, int> groupSizes;
        for (int i = 0; i < n; i++) {
            groupSizes[find(i)]++;
        }
        
        int maxGroups = groupSizes.size();
        int maxSize = 0;
        for (auto& [group, size] : groupSizes) {
            maxSize = max(maxSize, size);
        }
        
        return {maxGroups, maxSize};
    }
}; 