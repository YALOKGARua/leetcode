class Solution {
public:
    int maxRepeating(string sequence, string word) {
        int maxK = 0;
        string current = word;
        
        while (sequence.find(current) != string::npos) {
            maxK++;
            current += word;
        }
        
        return maxK;
    }
}; 