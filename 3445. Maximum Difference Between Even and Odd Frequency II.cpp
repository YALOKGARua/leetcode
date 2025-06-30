#include <string>

using namespace std;

class Solution {
public:
    int maxDifference(string s, int k) {
        const int n = s.length();
        int result = -2e9;
        
        for (int i = 0; i <= n - k; ++i) {
            int freq[5] = {};
            
            for (int j = i; j < n; ++j) {
                ++freq[s[j] - '0'];
                
                if (j - i + 1 >= k) {
                    int maxOdd = 0, minEven = 2e9;
                    bool hasOdd = false, hasEven = false;
                    
                    for (int ch = 0; ch < 5; ++ch) {
                        if (freq[ch] > 0) {
                            if (freq[ch] & 1) {
                                if (freq[ch] > maxOdd) maxOdd = freq[ch];
                                hasOdd = true;
                            } else {
                                if (freq[ch] < minEven) minEven = freq[ch];
                                hasEven = true;
                            }
                        }
                    }
                    
                    if (hasOdd && hasEven && maxOdd - minEven > result) {
                        result = maxOdd - minEven;
                    }
                }
            }
        }
        
        return result;
    }
};
