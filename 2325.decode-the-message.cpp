#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string decodeMessage(string key, string message) {
        vector<char> mapping(26);
        vector<bool> used(26, false);
        int index = 0;
        
        for (char c : key) {
            if (c != ' ' && !used[c - 'a']) {
                mapping[c - 'a'] = 'a' + index;
                used[c - 'a'] = true;
                index++;
            }
        }
        
        string result = "";
        for (char c : message) {
            if (c == ' ') {
                result += ' ';
            } else {
                result += mapping[c - 'a'];
            }
        }
        
        return result;
    }
}; 