from typing import List
from collections import defaultdict

class Solution:
    def placedCoins(self, edges: List[List[int]], cost: List[int]) -> List[int]:
        n = len(cost)
        graph = defaultdict(list)
        
        for a, b in edges:
            graph[a].append(b)
            graph[b].append(a)
            
        def dfs(node: int, parent: int) -> tuple:
            subtree_costs = [cost[node]]
            subtree_size = 1
            
            for child in graph[node]:
                if child != parent:
                    child_costs, child_size = dfs(child, node)
                    subtree_costs.extend(child_costs)
                    subtree_size += child_size
                    
            return subtree_costs, subtree_size
            
        result = [0] * n
        
        def calculate_coins(node: int, parent: int):
            costs, size = dfs(node, parent)
            
            if size < 3:
                result[node] = 1
            else:
                costs.sort()
                max_product = max(
                    costs[-1] * costs[-2] * costs[-3],
                    costs[0] * costs[1] * costs[-1]
                )
                result[node] = max(0, max_product)
                
            for child in graph[node]:
                if child != parent:
                    calculate_coins(child, node)
                    
        calculate_coins(0, -1)
        return result 