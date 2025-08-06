class Solution {
public:
    string stringHash(string s, int k) {
        string result;
        int n = s.length();
        for (int i = 0; i < n; i += k) {
            int sum = 0;
            for (int j = 0; j < k; ++j) {
                sum += s[i + j] - 'a';
            }
            int hashedChar = sum % 26;
            result += 'a' + hashedChar;
        }
        return result;
    }
}; 