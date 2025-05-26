from typing import List

class Solution:
    def closestCost(self, baseCosts: List[int], toppingCosts: List[int], target: int) -> int:
        result = float('inf')
        
        def dfs(index, curr_cost):
            nonlocal result
            if abs(curr_cost - target) < abs(result - target) or \
               (abs(curr_cost - target) == abs(result - target) and curr_cost < result):
                result = curr_cost
                
            if index == len(toppingCosts):
                return
                
            for i in range(3):
                dfs(index + 1, curr_cost + i * toppingCosts[index])
                
        for base in baseCosts:
            dfs(0, base)
            
        return result 