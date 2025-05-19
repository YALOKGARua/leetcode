/**
 * @param {string[]} words
 * @param {number[]} groups
 * @return {string[]}
 */
var getWordsInLongestSubsequence = function(words, groups) {
    const n = words.length;
    const hammingDistance = (str1, str2) => {
        if (str1.length !== str2.length) return Infinity;
        
        let distance = 0;
        for (let i = 0; i < str1.length; i++) {
            if (str1[i] !== str2[i]) distance++;
        }
        return distance;
    };
    
    const dp = Array(n).fill(1);
    const prev = Array(n).fill(-1);
    
    for (let i = 1; i < n; i++) {
        for (let j = 0; j < i; j++) {
            if (groups[i] !== groups[j] && 
                hammingDistance(words[i], words[j]) === 1 &&
                dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                prev[i] = j;
            }
        }
    }
    
    let maxIdx = 0;
    for (let i = 1; i < n; i++) {
        if (dp[i] > dp[maxIdx]) maxIdx = i;
    }
    
    const result = [];
    while (maxIdx !== -1) {
        result.unshift(words[maxIdx]);
        maxIdx = prev[maxIdx];
    }
    
    return result;
}; 