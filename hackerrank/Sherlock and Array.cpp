string balancedSums(vector<int> arr) {
    int n = arr.size();
    
    if (n == 0) return "NO";
    if (n == 1) return "YES";
    
    long long totalSum = 0;
    for (int i = 0; i < n; i++) {
        totalSum += arr[i];
    }
    
    long long leftSum = 0;
    
    for (int i = 0; i < n; i++) {
        long long rightSum = totalSum - leftSum - arr[i];
        
        if (leftSum == rightSum) {
            return "YES";
        }
        
        leftSum += arr[i];
    }
    
    return "NO";
}
