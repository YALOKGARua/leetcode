class Solution {
public:
    int divisorSubstrings(int num, int k) {
        string s = to_string(num);
        int count = 0;
        for (int i = 0; i <= s.length() - k; ++i) {
            string substring = s.substr(i, k);
            int divisor = stoi(substring);
            if (divisor != 0 && num % divisor == 0) {
                count++;
            }
        }
        return count;
    }
}; 