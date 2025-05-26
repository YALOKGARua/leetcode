class Solution:
    def minimumScore(self, s: str, t: str) -> int:
        m, n = len(s), len(t)
        
        def is_subsequence(s, t):
            i = j = 0
            while i < len(s) and j < len(t):
                if s[i] == t[j]:
                    j += 1
                i += 1
            return j == len(t)
            
        if is_subsequence(s, t):
            return 0
            
        result = n
        for i in range(n):
            for j in range(i, n):
                new_t = t[:i] + t[j+1:]
                if is_subsequence(s, new_t):
                    result = min(result, j - i + 1)
                    
        return result 