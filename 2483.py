class Solution:
    def bestClosingTime(self, customers: str) -> int:
        n = len(customers)
        prefix_n = [0] * (n + 1)
        suffix_y = [0] * (n + 1)
        
        for i in range(n):
            prefix_n[i + 1] = prefix_n[i] + (1 if customers[i] == 'N' else 0)
            
        for i in range(n-1, -1, -1):
            suffix_y[i] = suffix_y[i + 1] + (1 if customers[i] == 'Y' else 0)
            
        min_penalty = float('inf')
        best_hour = 0
        
        for i in range(n + 1):
            penalty = prefix_n[i] + suffix_y[i]
            if penalty < min_penalty:
                min_penalty = penalty
                best_hour = i
                
        return best_hour 