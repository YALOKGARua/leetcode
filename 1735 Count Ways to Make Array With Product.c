#define MOD 1000000007
#define MAX_N 20005

long long fact[MAX_N];
long long invFact[MAX_N];

long long modPow(long long base, long long exp) {
    long long result = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return result;
}

void precompute() {
    fact[0] = 1;
    for (int i = 1; i < MAX_N; i++) {
        fact[i] = (fact[i-1] * i) % MOD;
    }
    
    invFact[MAX_N-1] = modPow(fact[MAX_N-1], MOD-2);
    for (int i = MAX_N-2; i >= 0; i--) {
        invFact[i] = (invFact[i+1] * (i+1)) % MOD;
    }
}

long long combination(int n, int k) {
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;
    if (n >= MAX_N) return 0;  // Защита от выхода за границы
    return ((fact[n] * invFact[k]) % MOD * invFact[n-k]) % MOD;
}

int* waysToFillArray(int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    precompute();
    
    int* result = (int*)malloc(queriesSize * sizeof(int));
    *returnSize = queriesSize;
    
    for (int i = 0; i < queriesSize; i++) {
        int n = queries[i][0];
        int k = queries[i][1];
        
        if (k == 1) {
            result[i] = 1;
            continue;
        }
        
        long long ways = 1;
        int temp = k;
        
        for (int p = 2; p * p <= temp; p++) {
            if (temp % p == 0) {
                int count = 0;
                while (temp % p == 0) {
                    count++;
                    temp /= p;
                }
                if (count + n - 1 < MAX_N) {
                    ways = (ways * combination(count + n - 1, count)) % MOD;
                }
            }
        }
        
        if (temp > 1) {
            ways = (ways * n) % MOD;
        }
        
        result[i] = (int)ways;
    }
    
    return result;
} 