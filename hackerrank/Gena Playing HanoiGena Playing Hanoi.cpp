vector<int> dp;

int hanoi4(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (n == 2) return 3;
    if (dp[n] != -1) return dp[n];
    
    int result = (1 << n) - 1;
    for (int i = 1; i < n; i++) {
        result = min(result, 2 * hanoi4(i) + (1 << (n - i)) - 1);
    }
    
    return dp[n] = result;
}

int hanoi(vector<int> posts) {
    int n = posts.size();
    dp.assign(n + 1, -1);
    
    int result = 0;
    vector<bool> solved(n, false);
    
    for (int i = n - 1; i >= 0; i--) {
        bool canPlace = true;
        
        if (posts[i] != 1) {
            canPlace = false;
        } else {
            for (int j = 0; j < i; j++) {
                if (posts[j] == 1 && !solved[j]) {
                    canPlace = false;
                    break;
                }
            }
        }
        
        if (canPlace) {
            solved[i] = true;
        } else {
            result += hanoi4(i + 1);
            for (int j = 0; j <= i; j++) {
                solved[j] = true;
            }
        }
    }
    
    return result;
}
