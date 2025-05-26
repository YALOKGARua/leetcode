from typing import List

class Solution:
    def minimumRemoval(self, beans: List[int]) -> int:
        n = len(beans)
        beans.sort()
        total = sum(beans)
        result = float('inf')
        
        for i in range(n):
            curr = total - (n - i) * beans[i]
            result = min(result, curr)
            
        return result 