class Solution {
private:
    int getDistance(char a, char b) {
        int dist = abs(a - b);
        return min(dist, 26 - dist);
    }
    
public:
    string getSmallestString(string s, int k) {
        int n = s.length();
        string result = s;
        
        for (int i = 0; i < n; i++) {
            char current = s[i];
            char best = 'a';
            int minDist = getDistance(current, 'a');
            
            for (char c = 'a'; c <= 'z'; c++) {
                int dist = getDistance(current, c);
                if (dist < minDist) {
                    minDist = dist;
                    best = c;
                }
            }
            
            result[i] = best;
            k -= minDist;
        }
        
        if (k < 0) {
            return s;
        }
        
        for (int i = 0; i < n && k > 0; i++) {
            char current = result[i];
            char original = s[i];
            
            for (char c = 'a'; c <= 'z'; c++) {
                int newDist = getDistance(original, c);
                int oldDist = getDistance(original, current);
                int diff = newDist - oldDist;
                
                if (diff <= k && c < current) {
                    result[i] = c;
                    k -= diff;
                    break;
                }
            }
        }
        
        return result;
    }
}; 