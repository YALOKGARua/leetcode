class Solution:
    def splitString(self, s: str) -> bool:
        def backtrack(index: int, prev_val: int, count: int) -> bool:
            if index == len(s) and count >= 2:
                return True
                
            for i in range(index, len(s)):
                curr_val = int(s[index:i+1])
                
                if prev_val == -1 or curr_val == prev_val - 1:
                    if backtrack(i + 1, curr_val, count + 1):
                        return True
                        
            return False
            
        return backtrack(0, -1, 0) 