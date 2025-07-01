int shortPalindrome(string s) {
    const int MOD = 1000000007;
    int n = s.length();
    
    vector<long long> dp1(26, 0);
    long long dp2 = 0;
    vector<long long> dp3(26, 0);
    long long result = 0;
    
    for (int i = 0; i < n; i++) {
        int c = s[i] - 'a';
        
        result = (result + dp3[c]) % MOD;
        dp3[c] = (dp3[c] + dp2) % MOD;
        dp2 = (dp2 + dp1[c]) % MOD;
        dp1[c]++;
    }
    
    return (int)result;
}