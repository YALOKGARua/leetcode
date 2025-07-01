int pairs(int k, vector<int> arr) {
    set<int> numbers;
    
    for (size_t i = 0; i < arr.size(); i++) {
        numbers.insert(arr[i]);
    }
    
    int pairCount = 0;
    
    for (set<int>::iterator it = numbers.begin(); it != numbers.end(); ++it) {
        int current = *it;
        int target = current + k;
        
        if (numbers.find(target) != numbers.end()) {
            pairCount++;
        }
    }
    
    return pairCount;
}
