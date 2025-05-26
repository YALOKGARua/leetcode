from typing import List

class Solution:
    def numberOfAlternatingGroups(self, colors: List[int], k: int) -> int:
        n = len(colors)
        result = 0
        for i in range(n):
            valid = True
            for j in range(k):
                curr = (i + j) % n
                next_pos = (i + j + 1) % n
                if j < k - 1 and colors[curr] == colors[next_pos]:
                    valid = False
                    break
            if valid:
                result += 1
                
        return result 