class Solution:
    def minInteger(self, num: str, k: int) -> str:
        n = len(num)
        if k == 0:
            return num
            
        result = []
        remaining = list(num)
        
        while k > 0 and remaining:
            min_digit = '9'
            min_pos = 0
            
            left = 0
            right = min(k, len(remaining) - 1)
            
            while left <= right:
                mid = (left + right) // 2
                if remaining[mid] < min_digit:
                    min_digit = remaining[mid]
                    min_pos = mid
                    right = mid - 1
                else:
                    left = mid + 1
                    
            if min_pos == 0:
                result.append(remaining.pop(0))
            else:
                k -= min_pos
                result.append(remaining.pop(min_pos))
                
        result.extend(remaining)
        return ''.join(result) 