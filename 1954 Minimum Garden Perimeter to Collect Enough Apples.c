long long minimumPerimeter(long long neededApples) {
    long long left = 1;
    long long right = 100000;
    
    while (left <= right) {
        long long k = (left + right) / 2;
        long long apples = 2 * k * (k + 1) * (2 * k + 1);
        
        if (apples >= neededApples) {
            right = k - 1;
        } else {
            left = k + 1;
        }
    }
    
    return left * 8;
} 