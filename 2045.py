from typing import List
from collections import defaultdict
import heapq

class Solution:
    def secondMinimum(self, n: int, edges: List[List[int]], time: int, change: int) -> int:
        graph = defaultdict(list)
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)
            
        def get_wait_time(curr_time):
            if (curr_time // change) % 2 == 0:
                return 0
            return change - (curr_time % change)
            
        times = []
        heap = [(0, 1)]
        visited = set()
        
        while heap and len(times) < 2:
            curr_time, node = heapq.heappop(heap)
            
            if node == n:
                if curr_time not in times:
                    times.append(curr_time)
                continue
                
            if (curr_time, node) in visited:
                continue
            visited.add((curr_time, node))
            
            wait_time = get_wait_time(curr_time)
            next_time = curr_time + wait_time + time
            
            for neighbor in graph[node]:
                heapq.heappush(heap, (next_time, neighbor))
                
        return times[1] if len(times) > 1 else -1 