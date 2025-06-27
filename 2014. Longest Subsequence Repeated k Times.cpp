class Solution {
public:
    string longestSubsequenceRepeatedK(string s, int k) {
        vector<int> cnt(26, 0);
        for (char c : s) {
            cnt[c - 'a']++;
        }
        
        string chars;
        for (int i = 0; i < 26; i++) {
            if (cnt[i] >= k) {
                chars += (char)('a' + i);
            }
        }
        
        string result = "";
        queue<string> q;
        q.push("");
        
        while (!q.empty()) {
            int sz = q.size();
            string best = "";
            
            for (int i = 0; i < sz; i++) {
                string curr = q.front();
                q.pop();
                
                if (curr > best) {
                    best = curr;
                }
                
                for (char c : chars) {
                    string next = curr + c;
                    if (canForm(s, next, k)) {
                        q.push(next);
                    }
                }
            }
            
            if (!best.empty()) {
                result = best;
            }
        }
        
        return result;
    }
    
private:
    bool canForm(const string& s, const string& pattern, int k) {
        if (pattern.empty()) return true;
        
        int n = s.length();
        int m = pattern.length();
        
        if (m * k > n) return false;
        
        int pos = 0;
        for (int rep = 0; rep < k; rep++) {
            for (char c : pattern) {
                while (pos < n && s[pos] != c) {
                    pos++;
                }
                if (pos >= n) return false;
                pos++;
            }
        }
        return true;
    }
};
