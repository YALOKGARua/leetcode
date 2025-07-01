int minimumLoss(vector<long> price) {
    int n = price.size();
    set<long> futurePrices;
    long minLoss = LONG_MAX;
    
    for (int i = n - 1; i >= 0; i--) {
        long buyPrice = price[i];
        
        auto it = futurePrices.lower_bound(buyPrice);
        if (it != futurePrices.begin()) {
            --it;
            long sellPrice = *it;
            long loss = buyPrice - sellPrice;
            minLoss = min(minLoss, loss);
        }
        
        futurePrices.insert(buyPrice);
    }
    
    return (int)minLoss;
}
