from typing import List
import heapq

class Solution:
    def minCost(self, maxTime: int, edges: List[List[int]], passingFees: List[int]) -> int:
        n = len(passingFees)
        graph = [[] for _ in range(n)]
        
        for x, y, time in edges:
            graph[x].append((y, time))
            graph[y].append((x, time))
            
        heap = [(passingFees[0], 0, 0)]
        visited = {}
        
        while heap:
            cost, time, city = heapq.heappop(heap)
            
            if city == n - 1:
                return cost
                
            if city in visited and visited[city] <= time:
                continue
                
            visited[city] = time
            
            for next_city, edge_time in graph[city]:
                new_time = time + edge_time
                if new_time <= maxTime:
                    new_cost = cost + passingFees[next_city]
                    if next_city not in visited or visited[next_city] > new_time:
                        heapq.heappush(heap, (new_cost, new_time, next_city))
                        
        return -1 