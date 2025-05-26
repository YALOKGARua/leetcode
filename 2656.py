from typing import List
import heapq

class Solution:
    def maximizeSum(self, nums: List[int], k: int) -> int:
        heap = []
        for num in nums:
            heapq.heappush(heap, -num)
            
        total = 0
        for _ in range(k):
            curr = -heapq.heappop(heap)
            total += curr
            heapq.heappush(heap, -(curr + 1))
            
        return total 