int concatenatedBinary(int n) {
    long long result = 0;
    long long mod = 1000000007;
    int len = 0;
    
    for (int i = 1; i <= n; i++) {
        if ((i & (i - 1)) == 0) {
            len++;
        }
        
        result = ((result << len) | i) % mod;
    }
    
    return (int)result;
} 