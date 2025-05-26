from collections import Counter

class Solution:
    def validSubstringCount(self, word1: str, word2: str) -> int:
        n1, n2 = len(word1), len(word2)
        if n1 < n2:
            return 0
            
        target = Counter(word2)
        result = 0
        
        for i in range(n1):
            curr = Counter()
            for j in range(i, min(i + 100, n1)):
                curr[word1[j]] += 1
                if j - i + 1 >= n2:
                    valid = True
                    for char, count in target.items():
                        if curr[char] < count:
                            valid = False
                            break
                    if valid:
                        result += 1
                        
        return result 