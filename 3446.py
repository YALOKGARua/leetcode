from typing import List

class Solution:
    def sortMatrix(self, grid: List[List[int]]) -> List[List[int]]:
        n = len(grid)
        
        def get_diagonal(i: int, j: int) -> List[int]:
            diagonal = []
            while i < n and j < n:
                diagonal.append(grid[i][j])
                i += 1
                j += 1
            return diagonal
            
        def set_diagonal(i: int, j: int, values: List[int]) -> None:
            for val in values:
                grid[i][j] = val
                i += 1
                j += 1
                
        for i in range(n):
            diagonal = get_diagonal(i, 0)
            diagonal.sort(reverse=True)
            set_diagonal(i, 0, diagonal)
            
        for j in range(1, n):
            diagonal = get_diagonal(0, j)
            diagonal.sort()
            set_diagonal(0, j, diagonal)
            
        return grid 