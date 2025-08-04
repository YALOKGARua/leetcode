#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    string largestWordCount(vector<string>& messages, vector<string>& senders) {
        unordered_map<string, int> wordCount;
        
        for (int i = 0; i < messages.size(); i++) {
            string sender = senders[i];
            string message = messages[i];
            
            int count = 1;
            for (char c : message) {
                if (c == ' ') count++;
            }
            
            wordCount[sender] += count;
        }
        
        string result = "";
        int maxCount = 0;
        
        for (auto& [sender, count] : wordCount) {
            if (count > maxCount || (count == maxCount && sender > result)) {
                maxCount = count;
                result = sender;
            }
        }
        
        return result;
    }
}; 