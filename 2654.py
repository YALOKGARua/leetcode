from typing import List
from math import gcd

class Solution:
    def minOperations(self, nums: List[int]) -> int:
        n = len(nums)
        if 1 in nums:
            return n - nums.count(1)
            
        min_ops = float('inf')
        for i in range(n):
            curr_gcd = nums[i]
            for j in range(i + 1, n):
                curr_gcd = gcd(curr_gcd, nums[j])
                if curr_gcd == 1:
                    min_ops = min(min_ops, j - i + n - 1)
                    break
                    
        return min_ops if min_ops != float('inf') else -1 