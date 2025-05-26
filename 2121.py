from typing import List, Dict, Set, Tuple
from collections import defaultdict
from dataclasses import dataclass
from enum import Enum
import math

class IntervalType(Enum):
    LEFT = "LEFT"
    RIGHT = "RIGHT"
    BOTH = "BOTH"

@dataclass
class IntervalInfo:
    value: int
    index: int
    type: IntervalType
    left_count: int = 0
    right_count: int = 0
    left_sum: int = 0
    right_sum: int = 0

class IntervalCalculator:
    def __init__(self, arr: List[int]):
        self.arr = arr
        self.n = len(arr)
        self.value_indices = defaultdict(list)
        self.interval_info = {}
        
    def collect_indices(self):
        for i, val in enumerate(self.arr):
            self.value_indices[val].append(i)
            
    def calculate_interval_info(self):
        for val, indices in self.value_indices.items():
            if len(indices) == 1:
                self.interval_info[indices[0]] = IntervalInfo(
                    value=val,
                    index=indices[0],
                    type=IntervalType.BOTH
                )
                continue
                
            for i, idx in enumerate(indices):
                info = IntervalInfo(
                    value=val,
                    index=idx,
                    type=IntervalType.BOTH
                )
                
                if i > 0:
                    info.left_count = i
                    info.left_sum = sum(abs(idx - indices[j]) for j in range(i))
                    
                if i < len(indices) - 1:
                    info.right_count = len(indices) - i - 1
                    info.right_sum = sum(abs(idx - indices[j]) for j in range(i + 1, len(indices)))
                    
                self.interval_info[idx] = info
                
    def optimize_intervals(self):
        for val, indices in self.value_indices.items():
            if len(indices) <= 1:
                continue
                
            for i in range(1, len(indices)):
                prev_idx = indices[i-1]
                curr_idx = indices[i]
                diff = curr_idx - prev_idx
                
                self.interval_info[curr_idx].left_sum = (
                    self.interval_info[prev_idx].left_sum +
                    self.interval_info[prev_idx].left_count * diff
                )
                
            for i in range(len(indices)-2, -1, -1):
                next_idx = indices[i+1]
                curr_idx = indices[i]
                diff = next_idx - curr_idx
                
                self.interval_info[curr_idx].right_sum = (
                    self.interval_info[next_idx].right_sum +
                    self.interval_info[next_idx].right_count * diff
                )
                
    def get_total_intervals(self) -> List[int]:
        result = [0] * self.n
        for idx, info in self.interval_info.items():
            result[idx] = info.left_sum + info.right_sum
        return result

class Solution:
    def getDistances(self, arr: List[int]) -> List[int]:
        n = len(arr)
        value_indices = defaultdict(list)
        
        for i, val in enumerate(arr):
            value_indices[val].append(i)
            
        result = [0] * n
        
        for indices in value_indices.values():
            if len(indices) == 1:
                continue
                
            total = sum(abs(indices[0] - j) for j in indices[1:])
            result[indices[0]] = total
            
            for i in range(1, len(indices)):
                diff = indices[i] - indices[i-1]
                total += (i * diff) - ((len(indices) - i) * diff)
                result[indices[i]] = total
                
        return result 