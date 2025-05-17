int valueAfterKSeconds(int n, int k) {
    const int MOD = 1000000007;
    int* curr = (int*)malloc(n * sizeof(int));
    int* next = (int*)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        curr[i] = 1;
    }
    
    for (int sec = 0; sec < k; sec++) {
        next[0] = 1;
        int prefix_sum = 1;
        
        for (int i = 1; i < n; i++) {
            next[i] = (prefix_sum + curr[i]) % MOD;
            prefix_sum = (prefix_sum + curr[i]) % MOD;
        }
        
        int* temp = curr;
        curr = next;
        next = temp;
    }
    
    int result = curr[n-1];
    free(curr);
    free(next);
    return result;
} 