#include <string>
#include <cctype>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool isValid(const string& word) {
        if (word.length() < 3) return false;
        bool hasVowel = false;
        bool hasConsonant = false;
        const unordered_set<char> vowels = {'a','e','i','o','u','A','E','I','O','U'};
        for (char ch : word) {
            if (!isalnum(ch)) return false;
            if (isalpha(ch)) {
                if (vowels.count(ch)) {
                    hasVowel = true;
                } else {
                    hasConsonant = true;
                }
            }
        }
        return hasVowel && hasConsonant;
    }
};
