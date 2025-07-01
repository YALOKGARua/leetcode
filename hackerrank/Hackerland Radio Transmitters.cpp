int hackerlandRadioTransmitters(vector<int> x, int k) {
    set<int> uniquePositions(x.begin(), x.end());
    vector<int> houses(uniquePositions.begin(), uniquePositions.end());
    
    int transmitters = 0;
    int currentIndex = 0;
    int n = houses.size();
    
    while (currentIndex < n) {
        int leftmostUncovered = houses[currentIndex];
        int rightmostReachable = leftmostUncovered + k;
        
        int transmitterPosition = leftmostUncovered;
        while (currentIndex < n && houses[currentIndex] <= rightmostReachable) {
            transmitterPosition = houses[currentIndex];
            currentIndex++;
        }
        
        transmitters++;
        int coverageEnd = transmitterPosition + k;
        
        while (currentIndex < n && houses[currentIndex] <= coverageEnd) {
            currentIndex++;
        }
    }
    
    return transmitters;
}
