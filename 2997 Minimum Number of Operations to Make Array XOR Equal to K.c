int minOperations(int* nums, int numsSize, int k) {
    int xor_sum = 0;
    for (int i = 0; i < numsSize; i++) {
        xor_sum ^= nums[i];
    }
    
    int diff = xor_sum ^ k;
    
    int count = 0;
    while (diff > 0) {
        count += diff & 1;
        diff >>= 1;
    }
    
    return count;
} 