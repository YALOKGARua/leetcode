from typing import List
from collections import defaultdict

class Solution:
    def longestCommonPrefix(self, words: List[str], k: int) -> List[int]:
        n = len(words)
        if n <= k:
            return [0] * n
            
        def get_lcp(s1: str, s2: str) -> int:
            i = 0
            while i < len(s1) and i < len(s2) and s1[i] == s2[i]:
                i += 1
            return i
            
        def find_max_lcp(exclude_idx: int) -> int:
            remaining = words[:exclude_idx] + words[exclude_idx + 1:]
            if len(remaining) < k:
                return 0
                
            if k == 1:
                return max(len(word) for word in remaining)
                
            word_counts = defaultdict(int)
            for word in remaining:
                word_counts[word] += 1
                
            max_lcp = 0
            for word, count in word_counts.items():
                if count >= k:
                    return len(word)
                    
            if len(remaining) == k:
                min_lcp = float('inf')
                for i in range(len(remaining)):
                    for j in range(i + 1, len(remaining)):
                        lcp = get_lcp(remaining[i], remaining[j])
                        min_lcp = min(min_lcp, lcp)
                return min_lcp
                
            return 0
            
        return [find_max_lcp(i) for i in range(n)] 