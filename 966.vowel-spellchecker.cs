/*
 * @lc app=leetcode id=966 lang=csharp
 *
 * [966] Vowel Spellchecker
 *
 * https://leetcode.com/problems/vowel-spellchecker/description/
 *
 * algorithms
 * Medium (51.53%)
 * Likes:    439
 * Dislikes: 818
 * Total Accepted:    45.7K
 * Total Submissions: 88.7K
 * Testcase Example:  '["KiTe","kite","hare","Hare"]\n' +
  '["kite","Kite","KiTe","Hare","HARE","Hear","hear","keti","keet","keto"]'
 *
 * Given a wordlist, we want to implement a spellchecker that converts a query
 * word into a correct word.
 * 
 * For a given query word, the spell checker handles two categories of spelling
 * mistakes:
 * 
 * 
 * Capitalization: If the query matches a word in the wordlist
 * (case-insensitive), then the query word is returned with the same case as
 * the case in the wordlist.
 * 
 * 
 * Example: wordlist = ["yellow"], query = "YellOw": correct = "yellow"
 * Example: wordlist = ["Yellow"], query = "yellow": correct = "Yellow"
 * Example: wordlist = ["yellow"], query = "yellow": correct =
 * "yellow"
 * 
 * 
 * Vowel Errors: If after replacing the vowels ('a', 'e', 'i', 'o', 'u') of the
 * query word with any vowel individually, it matches a word in the wordlist
 * (case-insensitive), then the query word is returned with the same case as
 * the match in the wordlist.
 * 
 * Example: wordlist = ["YellOw"], query = "yollow": correct = "YellOw"
 * Example: wordlist = ["YellOw"], query = "yeellow": correct = "" (no
 * match)
 * Example: wordlist = ["YellOw"], query = "yllw": correct = "" (no
 * match)
 * 
 * 
 * 
 * 
 * In addition, the spell checker operates under the following precedence
 * rules:
 * 
 * 
 * When the query exactly matches a word in the wordlist (case-sensitive), you
 * should return the same word back.
 * When the query matches a word up to capitlization, you should return the
 * first such match in the wordlist.
 * When the query matches a word up to vowel errors, you should return the
 * first such match in the wordlist.
 * If the query has no matches in the wordlist, you should return the empty
 * string.
 * 
 * 
 * Given some queries, return a list of words answer, where answer[i] is the
 * correct word for query = queries[i].
 * 
 * 
 * Example 1:
 * Input: wordlist = ["KiTe","kite","hare","Hare"], queries =
 * ["kite","Kite","KiTe","Hare","HARE","Hear","hear","keti","keet","keto"]
 * Output: ["kite","KiTe","KiTe","Hare","hare","","","KiTe","","KiTe"]
 * Example 2:
 * Input: wordlist = ["yellow"], queries = ["YellOw"]
 * Output: ["yellow"]
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= wordlist.length, queries.length <= 5000
 * 1 <= wordlist[i].length, queries[i].length <= 7
 * wordlist[i] and queries[i] consist only of only English letters.
 * 
 * 
 */

// @lc code=start
using System;
using System.Collections.Generic;

public class Solution {
    public string[] Spellchecker(string[] wordlist, string[] queries) {
        HashSet<string> exactWords = new HashSet<string>();
        Dictionary<string, string> caseInsensitive = new Dictionary<string, string>();
        Dictionary<string, string> vowelInsensitive = new Dictionary<string, string>();
        
        foreach (string word in wordlist) {
            exactWords.Add(word);
            
            string lower = word.ToLower();
            if (!caseInsensitive.ContainsKey(lower)) {
                caseInsensitive[lower] = word;
            }
            
            string devoweled = ReplaceVowels(lower);
            if (!vowelInsensitive.ContainsKey(devoweled)) {
                vowelInsensitive[devoweled] = word;
            }
        }
        
        string[] result = new string[queries.Length];
        
        for (int i = 0; i < queries.Length; i++) {
            string query = queries[i];
            
            if (exactWords.Contains(query)) {
                result[i] = query;
                continue;
            }
            
            string lowerQuery = query.ToLower();
            if (caseInsensitive.ContainsKey(lowerQuery)) {
                result[i] = caseInsensitive[lowerQuery];
                continue;
            }
            
            string devoweled = ReplaceVowels(lowerQuery);
            if (vowelInsensitive.ContainsKey(devoweled)) {
                result[i] = vowelInsensitive[devoweled];
                continue;
            }
            
            result[i] = "";
        }
        
        return result;
    }
    
    private string ReplaceVowels(string word) {
        char[] chars = word.ToCharArray();
        for (int i = 0; i < chars.Length; i++) {
            if (IsVowel(chars[i])) {
                chars[i] = '*';
            }
        }
        return new string(chars);
    }
    
    private bool IsVowel(char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
}
// @lc code=end

