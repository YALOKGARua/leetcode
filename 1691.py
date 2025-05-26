from typing import List

class Solution:
    def maxHeight(self, cuboids: List[List[int]]) -> int:
        n = len(cuboids)
        
        for cuboid in cuboids:
            cuboid.sort()
            
        cuboids.sort()
        
        dp = [0] * n
        for i in range(n):
            dp[i] = cuboids[i][2]
            
        for i in range(n):
            for j in range(i):
                if (cuboids[i][0] >= cuboids[j][0] and 
                    cuboids[i][1] >= cuboids[j][1] and 
                    cuboids[i][2] >= cuboids[j][2]):
                    dp[i] = max(dp[i], dp[j] + cuboids[i][2])
                    
        return max(dp) 