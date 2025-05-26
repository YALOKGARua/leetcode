from typing import List, Dict, Set, Tuple
from collections import defaultdict

class Solution:
    def minimumScore(self, nums: List[int], edges: List[List[int]]) -> int:
        n = len(nums)
        graph = defaultdict(list)
        
        for a, b in edges:
            graph[a].append(b)
            graph[b].append(a)
            
        subtree_xor = {}
        parent = {}
        
        def compute_subtree_xor(node: int, p: int) -> int:
            parent[node] = p
            xor_val = nums[node]
            for child in graph[node]:
                if child != p:
                    xor_val ^= compute_subtree_xor(child, node)
            subtree_xor[node] = xor_val
            return xor_val
            
        compute_subtree_xor(0, -1)
        
        def get_component_xors(edge1: Tuple[int, int], edge2: Tuple[int, int]) -> List[int]:
            a1, b1 = edge1
            a2, b2 = edge2
            
            if parent[a1] == b1:
                a1, b1 = b1, a1
            if parent[a2] == b2:
                a2, b2 = b2, a2
                
            total_xor = subtree_xor[0]
            
            def is_ancestor(node: int, target: int) -> bool:
                while node != -1:
                    if node == target:
                        return True
                    node = parent[node]
                return False
                
            if is_ancestor(b1, b2):
                comp1 = subtree_xor[b2]
                comp2 = subtree_xor[b1] ^ subtree_xor[b2]
                comp3 = total_xor ^ subtree_xor[b1]
                return [comp1, comp2, comp3]
            elif is_ancestor(b2, b1):
                comp1 = subtree_xor[b1]
                comp2 = subtree_xor[b2] ^ subtree_xor[b1]
                comp3 = total_xor ^ subtree_xor[b2]
                return [comp1, comp2, comp3]
            else:
                comp1 = subtree_xor[b1]
                comp2 = subtree_xor[b2]
                comp3 = total_xor ^ comp1 ^ comp2
                return [comp1, comp2, comp3]
                
        min_score = float('inf')
        
        for i in range(len(edges)):
            for j in range(i + 1, len(edges)):
                edge1 = tuple(edges[i])
                edge2 = tuple(edges[j])
                
                xor_vals = get_component_xors(edge1, edge2)
                if len(xor_vals) == 3:
                    score = max(xor_vals) - min(xor_vals)
                    min_score = min(min_score, score)
                    
        return min_score 