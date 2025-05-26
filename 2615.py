from typing import List
from collections import defaultdict

class Solution:
    def distance(self, nums: List[int]) -> List[int]:
        n = len(nums)
        groups = defaultdict(list)
        
        for i, num in enumerate(nums):
            groups[num].append(i)
            
        result = [0] * n
        
        for indices in groups.values():
            if len(indices) == 1:
                continue
                
            total = sum(abs(indices[0] - j) for j in indices[1:])
            result[indices[0]] = total
            
            for i in range(1, len(indices)):
                diff = indices[i] - indices[i-1]
                total += diff * (i - 1) - diff * (len(indices) - i - 1)
                result[indices[i]] = total
                
        return result 