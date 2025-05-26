from typing import List
from collections import defaultdict

class Solution:
    def gcdSort(self, nums: List[int]) -> bool:
        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]
            
        def union(x, y):
            parent[find(x)] = find(y)
            
        def get_smallest_prime_factor(n):
            if n in spf:
                return spf[n]
            for p in primes:
                if p * p > n:
                    break
                if n % p == 0:
                    spf[n] = p
                    return p
            spf[n] = n
            return n
            
        def get_prime_factors(n):
            if n in factor_cache:
                return factor_cache[n]
            factors = set()
            while n > 1:
                p = get_smallest_prime_factor(n)
                factors.add(p)
                while n % p == 0:
                    n //= p
            factor_cache[n] = factors
            return factors
            
        max_num = max(nums)
        spf = {}
        factor_cache = {}
        primes = []
        is_prime = [True] * (max_num + 1)
        is_prime[0] = is_prime[1] = False
        for i in range(2, int(max_num ** 0.5) + 1):
            if is_prime[i]:
                for j in range(i * i, max_num + 1, i):
                    is_prime[j] = False
                    if j not in spf:
                        spf[j] = i
                primes.append(i)
                
        for i in range(int(max_num ** 0.5) + 1, max_num + 1):
            if is_prime[i]:
                primes.append(i)
                
        n = len(nums)
        parent = list(range(n))
        sorted_nums = sorted(nums)
        prime_to_indices = defaultdict(list)
        
        for i in range(n):
            factors = get_prime_factors(nums[i])
            for factor in factors:
                prime_to_indices[factor].append(i)
                
        for indices in prime_to_indices.values():
            for i in range(1, len(indices)):
                union(indices[i-1], indices[i])
                
        for i in range(n):
            if find(i) != find(nums.index(sorted_nums[i])):
                return False
                
        return True 