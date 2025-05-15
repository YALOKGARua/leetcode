#include <string>
using namespace std;

class Solution {
public:
    int wordToNum(string& word) {
        int num = 0;
        for (char c : word) {
            num = num * 10 + (c - 'a');
        }
        return num;
    }
    
    bool isSumEqual(string firstWord, string secondWord, string targetWord) {
        return wordToNum(firstWord) + wordToNum(secondWord) == wordToNum(targetWord);
    }
}; 