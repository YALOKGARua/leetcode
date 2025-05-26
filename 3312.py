from typing import List
import math
from collections import defaultdict
import bisect

class Solution:
    def gcdValues(self, nums: List[int], queries: List[int]) -> List[int]:
        n = len(nums)
        gcd_counts = defaultdict(int)
        
        for i in range(n):
            for j in range(i + 1, n):
                gcd_val = math.gcd(nums[i], nums[j])
                gcd_counts[gcd_val] += 1
                
        sorted_gcds = []
        prefix_sums = [0]
        gcd_values = []
        
        for gcd_val in sorted(gcd_counts.keys()):
            count = gcd_counts[gcd_val]
            sorted_gcds.extend([gcd_val] * count)
            prefix_sums.append(prefix_sums[-1] + count)
            gcd_values.append(gcd_val)
            
        result = []
        for q in queries:
            idx = bisect.bisect_right(prefix_sums, q) - 1
            result.append(gcd_values[idx])
            
        return result 