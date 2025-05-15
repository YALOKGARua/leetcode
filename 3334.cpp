#include <vector>
#include <numeric>
using namespace std;

class Solution {
private:
    long long gcd(long long a, long long b) {
        while (b) {
            a %= b;
            swap(a, b);
        }
        return a;
    }
    
    long long lcm(long long a, long long b) {
        return (a / gcd(a, b)) * b;
    }
    
    pair<long long, long long> getGcdLcm(vector<int>& nums, int skip) {
        if (nums.size() == 1) {
            return {nums[0], nums[0]};
        }
        
        long long currGcd = 0;
        long long currLcm = 1;
        
        for (int i = 0; i < nums.size(); i++) {
            if (i == skip) continue;
            if (currGcd == 0) {
                currGcd = nums[i];
                currLcm = nums[i];
            } else {
                currGcd = gcd(currGcd, nums[i]);
                currLcm = lcm(currLcm, nums[i]);
            }
        }
        return {currGcd, currLcm};
    }
    
public:
    long long maxScore(vector<int>& nums) {
        long long maxScore = 0;
        
        auto [gcd0, lcm0] = getGcdLcm(nums, -1);
        maxScore = gcd0 * lcm0;
    
        for (int i = 0; i < nums.size(); i++) {
            auto [currGcd, currLcm] = getGcdLcm(nums, i);
            maxScore = max(maxScore, currGcd * currLcm);
        }
        
        return maxScore;
    }
}; 