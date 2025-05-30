/*
 * @lc app=leetcode id=833 lang=csharp
 *
 * [833] Find And Replace in String
 *
 * https://leetcode.com/problems/find-and-replace-in-string/description/
 *
 * algorithms
 * Medium (51.32%)
 * Likes:    1215
 * Dislikes: 1041
 * Total Accepted:    159.9K
 * Total Submissions: 311.7K
 * Testcase Example:  '"abcd"\n[0, 2]\n["a", "cd"]\n["eee", "ffff"]'
 *
 * You are given a 0-indexed string s that you must perform k replacement
 * operations on. The replacement operations are given as three 0-indexed
 * parallel arrays, indices, sources, and targets, all of length k.
 * 
 * To complete the i^th replacement operation:
 * 
 * 
 * Check if the substring sources[i] occurs at index indices[i] in the original
 * string s.
 * If it does not occur, do nothing.
 * Otherwise if it does occur, replace that substring with targets[i].
 * 
 * 
 * For example, if s = "abcd", indices[i] = 0, sources[i] = "ab", and
 * targets[i] = "eee", then the result of this replacement will be "eeecd".
 * 
 * All replacement operations must occur simultaneously, meaning the
 * replacement operations should not affect the indexing of each other. The
 * testcases will be generated such that the replacements will not
 * overlap.
 * 
 * 
 * For example, a testcase with s = "abc", indices = [0, 1], and sources =
 * ["ab","bc"] will not be generated because the "ab" and "bc" replacements
 * overlap.
 * 
 * 
 * Return the resulting string after performing all replacement operations on
 * s.
 * 
 * A substring is a contiguous sequence of characters in a string.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "abcd", indices = [0, 2], sources = ["a", "cd"], targets =
 * ["eee", "ffff"]
 * Output: "eeebffff"
 * Explanation:
 * "a" occurs at index 0 in s, so we replace it with "eee".
 * "cd" occurs at index 2 in s, so we replace it with "ffff".
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "abcd", indices = [0, 2], sources = ["ab","ec"], targets =
 * ["eee","ffff"]
 * Output: "eeecd"
 * Explanation:
 * "ab" occurs at index 0 in s, so we replace it with "eee".
 * "ec" does not occur at index 2 in s, so we do nothing.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 1000
 * k == indices.length == sources.length == targets.length
 * 1 <= k <= 100
 * 0 <= indexes[i] < s.length
 * 1 <= sources[i].length, targets[i].length <= 50
 * s consists of only lowercase English letters.
 * sources[i] and targets[i] consist of only lowercase English letters.
 * 
 * 
 */

// @lc code=start
using System;
using System.Collections.Generic;
using System.Text;

public class Solution {
    public string FindReplaceString(string s, int[] indices, string[] sources, string[] targets) {
        var map = new Dictionary<int, int>();
        for (int i = 0; i < indices.Length; i++)
            if (indices[i] + sources[i].Length <= s.Length && s.Substring(indices[i], sources[i].Length) == sources[i])
                map[indices[i]] = i;
        var res = new StringBuilder();
        for (int i = 0; i < s.Length;) {
            if (map.ContainsKey(i)) {
                int idx = map[i];
                res.Append(targets[idx]);
                i += sources[idx].Length;
            } else {
                res.Append(s[i++]);
            }
        }
        return res.ToString();
    }
}
// @lc code=end

