#include <vector>
#include <map>
#include <algorithm>
#include <iterator>

using namespace std;

class Solution {
private:
    using FrequencyMap = map<int, int>;
    using MapIterator = FrequencyMap::const_iterator;
    
    template<typename Iterator>
    int computeHarmoniousLength(Iterator current, Iterator next) const {
        return (next->first - current->first == 1) ? 
               current->second + next->second : 0;
    }
    
    template<typename Container>
    FrequencyMap buildFrequencyDistribution(const Container& nums) const {
        FrequencyMap frequencies;
        for_each(nums.cbegin(), nums.cend(), 
                [&frequencies](const auto& value) {
                    frequencies[value]++;
                });
        return frequencies;
    }
    
    int findMaximumHarmoniousSequence(const FrequencyMap& frequencies) const {
        if (frequencies.size() < 2) return 0;
        
        int maxLength = 0;
        auto current = frequencies.cbegin();
        auto next = std::next(current);
        
        while (next != frequencies.cend()) {
            maxLength = max(maxLength, 
                          computeHarmoniousLength(current, next));
            advance(current, 1);
            advance(next, 1);
        }
        
        return maxLength;
    }
    
public:
    int findLHS(vector<int>& nums) {
        const auto frequencyDistribution = buildFrequencyDistribution(nums);
        return findMaximumHarmoniousSequence(frequencyDistribution);
    }
};
