class Solution:
    def minCuttingCost(self, n: int, m: int, k: int) -> int:
        if n <= k and m <= k:
            return 0
            
        if n > k and m > k:
            return min((n - k) * k, (m - k) * k)
            
        if n > k:
            return (n - k) * k
            
        return (m - k) * k 