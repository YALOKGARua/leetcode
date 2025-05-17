long long distributeCandies(int n, int limit) {
    long long total = 0;
    
    total = (long long)(n + 1) * (n + 2) / 2;
    
    if (n > limit) {
        long long over = n - limit - 1;
        total -= 3 * (over + 1) * (over + 2) / 2;
    }
    
    if (n > 2 * limit) {
        long long over = n - 2 * limit - 2;
        total += 3 * (over + 1) * (over + 2) / 2;
    }
     
    if (n > 3 * limit) {
        long long over = n - 3 * limit - 3;
        total -= (over + 1) * (over + 2) / 2;
    }
    
    return total;
} 