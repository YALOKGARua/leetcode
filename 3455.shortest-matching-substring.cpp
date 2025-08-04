class Solution {
private:
    vector<int> computeLPS(string pattern) {
        int m = pattern.length();
        vector<int> lps(m, 0);
        int len = 0;
        int i = 1;
        
        while (i < m) {
            if (pattern[i] == pattern[len]) {
                len++;
                lps[i] = len;
                i++;
            } else {
                if (len != 0) {
                    len = lps[len - 1];
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }
        return lps;
    }
    
    vector<int> findAllOccurrences(string text, string pattern) {
        vector<int> occurrences;
        int n = text.length();
        int m = pattern.length();
        
        if (m == 0) return occurrences;
        
        vector<int> lps = computeLPS(pattern);
        int i = 0, j = 0;
        
        while (i < n) {
            if (pattern[j] == text[i]) {
                i++;
                j++;
            }
            
            if (j == m) {
                occurrences.push_back(i - j);
                j = lps[j - 1];
            } else if (i < n && pattern[j] != text[i]) {
                if (j != 0) {
                    j = lps[j - 1];
                } else {
                    i++;
                }
            }
        }
        return occurrences;
    }
    
public:
    int shortestMatchingSubstring(string s, string p) {
        vector<string> parts;
        int starCount = 0;
        string current = "";
        
        for (char c : p) {
            if (c == '*') {
                if (!current.empty()) {
                    parts.push_back(current);
                    current = "";
                }
                starCount++;
            } else {
                current += c;
            }
        }
        if (!current.empty()) {
            parts.push_back(current);
        }
        
        if (starCount != 2) return -1;
        
        if (parts.empty()) return 0;
        if (parts.size() == 1) {
            vector<int> pos = findAllOccurrences(s, parts[0]);
            return pos.empty() ? -1 : parts[0].length();
        }
        
        vector<int> pos1 = findAllOccurrences(s, parts[0]);
        vector<int> pos2 = findAllOccurrences(s, parts[1]);
        vector<int> pos3;
        
        if (parts.size() == 3) {
            pos3 = findAllOccurrences(s, parts[2]);
        }
        
        int minLen = INT_MAX;
        
        for (int p1 : pos1) {
            int start = p1;
            int end1 = p1 + parts[0].length() - 1;
            
            auto it2 = lower_bound(pos2.begin(), pos2.end(), end1 + 1);
            if (it2 == pos2.end()) continue;
            
            int p2 = *it2;
            int end2 = p2 + parts[1].length() - 1;
            
            if (parts.size() == 3) {
                auto it3 = lower_bound(pos3.begin(), pos3.end(), end2 + 1);
                if (it3 == pos3.end()) continue;
                int p3 = *it3;
                int end3 = p3 + parts[2].length() - 1;
                minLen = min(minLen, end3 - start + 1);
            } else {
                minLen = min(minLen, end2 - start + 1);
            }
        }
        
        return minLen == INT_MAX ? -1 : minLen;
    }
}; 