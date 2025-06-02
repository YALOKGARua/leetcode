/*
 * @lc app=leetcode id=1078 lang=cpp
 *
 * [1078] Occurrences After Bigram
 *
 * https://leetcode.com/problems/occurrences-after-bigram/description/
 *
 * algorithms
 * Easy (63.66%)
 * Likes:    510
 * Dislikes: 364
 * Total Accepted:    83.1K
 * Total Submissions: 130.6K
 * Testcase Example:  '"alice is a good girl she is a good student"\n"a"\n"good"'
 *
 * Given two strings first and second, consider occurrences in some text of the
 * form "first second third", where second comes immediately after first, and
 * third comes immediately after second.
 * 
 * Return an array of all the words third for each occurrence of "first second
 * third".
 * 
 * 
 * Example 1:
 * Input: text = "alice is a good girl she is a good student", first = "a",
 * second = "good"
 * Output: ["girl","student"]
 * Example 2:
 * Input: text = "we will we will rock you", first = "we", second = "will"
 * Output: ["we","rock"]
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= text.length <= 1000
 * text consists of lowercase English letters and spaces.
 * All the words in text are separated by a single space.
 * 1 <= first.length, second.length <= 10
 * first and second consist of lowercase English letters.
 * text will not have any leading or trailing spaces.
 * 
 * 
 */

// @lc code=start
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class Solution {
public:
    vector<string> findOcurrences(string text, string first, string second) {
        vector<string> words;
        istringstream iss(text);
        string word;
        
        while (iss >> word) {
            words.push_back(word);
        }
        
        vector<string> result;
        for (int i = 0; i < words.size() - 2; i++) {
            if (words[i] == first && words[i + 1] == second) {
                result.push_back(words[i + 2]);
            }
        }
        
        return result;
    }
};
// @lc code=end

