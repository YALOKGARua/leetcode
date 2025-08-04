class Solution {
public:
    int countValidWords(string sentence) {
        int count = 0;
        stringstream ss(sentence);
        string token;
        
        while (ss >> token) {
            if (isValidWord(token)) {
                count++;
            }
        }
        
        return count;
    }
    
private:
    bool isValidWord(const string& token) {
        int n = token.length();
        if (n == 0) return false;
        
        bool hasHyphen = false;
        bool hasPunctuation = false;
        
        for (int i = 0; i < n; i++) {
            char c = token[i];
            
            if (isdigit(c)) {
                return false;
            }
            
            if (c == '-') {
                if (hasHyphen) return false;
                if (i == 0 || i == n - 1) return false;
                if (!isalpha(token[i-1]) || !isalpha(token[i+1])) return false;
                hasHyphen = true;
            }
            
            if (c == '!' || c == '.' || c == ',') {
                if (hasPunctuation) return false;
                if (i != n - 1) return false;
                hasPunctuation = true;
            }
        }
        
        return true;
    }
}; 