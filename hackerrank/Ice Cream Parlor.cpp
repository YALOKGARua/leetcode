vector<int> icecreamParlor(int m, vector<int> arr) {
    unordered_map<int, int> priceToIndex;
    
    for (int i = 0; i < arr.size(); i++) {
        int currentPrice = arr[i];
        int complement = m - currentPrice;
        
        if (priceToIndex.find(complement) != priceToIndex.end()) {
            int firstIndex = priceToIndex[complement];
            int secondIndex = i;
            
            if (firstIndex < secondIndex) {
                return vector<int>{firstIndex + 1, secondIndex + 1};
            } else {
                return vector<int>{secondIndex + 1, firstIndex + 1};
            }
        }
        
        priceToIndex[currentPrice] = i;
    }
    
    return vector<int>{};
}
