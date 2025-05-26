from typing import List

class Solution:
    def countWays(self, nums: List[int]) -> int:
        n = len(nums)
        nums.sort()
        result = 0
        
        for i in range(n + 1):
            if i > 0 and nums[i-1] >= i:
                continue
            if i < n and nums[i] <= i:
                continue
            result += 1
                
        return result 