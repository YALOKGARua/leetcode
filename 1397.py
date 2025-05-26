class Solution:
    def findGoodStrings(self, n: int, s1: str, s2: str, evil: str) -> int:
        MOD = 10**9 + 7
        m = len(evil)
        lps = [0] * m
        j = 0
        for i in range(1, m):
            while j > 0 and evil[i] != evil[j]:
                j = lps[j-1]
            if evil[i] == evil[j]:
                j += 1
            lps[i] = j
            
        @lru_cache(None)
        def dp(pos, is_lower, is_higher, evil_match):
            if evil_match == m:
                return 0
            if pos == n:
                return 1
                
            res = 0
            start = ord('a')
            end = ord('z')
            
            if not is_lower:
                start = ord(s1[pos])
            if not is_higher:
                end = ord(s2[pos])
                
            for c in range(start, end + 1):
                char = chr(c)
                new_is_lower = is_lower or char > s1[pos]
                new_is_higher = is_higher or char < s2[pos]
                new_evil_match = evil_match
                while new_evil_match > 0 and char != evil[new_evil_match]:
                    new_evil_match = lps[new_evil_match - 1]
                if char == evil[new_evil_match]:
                    new_evil_match += 1
                    
                res = (res + dp(pos + 1, new_is_lower, new_is_higher, new_evil_match)) % MOD
                
            return res
            
        return dp(0, False, False, 0) 