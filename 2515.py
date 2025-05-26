from typing import List

class Solution:
    def closestTarget(self, words: List[str], target: str, startIndex: int) -> int:
        n = len(words)
        if target not in words:
            return -1
            
        min_dist = float('inf')
        
        for i in range(n):
            if words[i] == target:
                dist = min(abs(i - startIndex), n - abs(i - startIndex))
                min_dist = min(min_dist, dist)
                
        return min_dist 