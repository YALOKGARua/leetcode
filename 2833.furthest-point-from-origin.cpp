class Solution {
public:
    int furthestDistanceFromOrigin(string moves) {
        int left = 0, right = 0, underscore = 0;
        for (char c : moves) {
            if (c == 'L') left++;
            else if (c == 'R') right++;
            else underscore++;
        }
        return abs(left - right) + underscore;
    }
}; 