#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    string entityParser(string text) {
        unordered_map<string, char> entities = {
            {"&quot;", '"'},
            {"&apos;", '\''},
            {"&amp;", '&'},
            {"&gt;", '>'},
            {"&lt;", '<'},
            {"&frasl;", '/'}
        };
        
        string result = "";
        int i = 0;
        
        while (i < text.length()) {
            if (text[i] == '&') {
                bool found = false;
                for (auto& [entity, replacement] : entities) {
                    if (i + entity.length() <= text.length() && 
                        text.substr(i, entity.length()) == entity) {
                        result += replacement;
                        i += entity.length();
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    result += text[i];
                    i++;
                }
            } else {
                result += text[i];
                i++;
            }
        }
        
        return result;
    }
}; 