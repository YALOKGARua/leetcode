#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minElement(vector<int>& nums) {
        int minVal = INT_MAX;
        
        for (int num : nums) {
            int digitSum = 0;
            int temp = num;
            
            while (temp > 0) {
                digitSum += temp % 10;
                temp /= 10;
            }
            
            minVal = min(minVal, digitSum);
        }
        
        return minVal;
    }
}; 