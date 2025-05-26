from typing import List
import bisect

class Solution:
    def numberOfPairs(self, nums1: List[int], nums2: List[int], diff: int) -> int:
        n = len(nums1)
        arr = []
        count = 0
        
        for i in range(n):
            val = nums1[i] - nums2[i]
            count += bisect.bisect_right(arr, val + diff)
            bisect.insort(arr, val)
            
        return count 