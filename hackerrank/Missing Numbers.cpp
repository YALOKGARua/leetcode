vector<int> missingNumbers(vector<int> arr, vector<int> brr) {
    map<int, int> freqArr;
    map<int, int> freqBrr;
    
    for (size_t i = 0; i < arr.size(); i++) {
        freqArr[arr[i]]++;
    }
    
    for (size_t i = 0; i < brr.size(); i++) {
        freqBrr[brr[i]]++;
    }
    
    vector<int> missing;
    
    for (map<int, int>::iterator it = freqBrr.begin(); it != freqBrr.end(); ++it) {
        int number = it->first;
        int countInBrr = it->second;
        int countInArr = freqArr[number];
        
        if (countInBrr > countInArr) {
            missing.push_back(number);
        }
    }
    
    return missing;
}
