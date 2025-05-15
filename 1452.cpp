#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

class Solution {
public:
    vector<int> peopleIndexes(vector<vector<string>>& favoriteCompanies) {
        int n = favoriteCompanies.size();
        vector<unordered_set<string>> sets(n);
        vector<int> result;
        
        for (int i = 0; i < n; i++) {
            for (const string& company : favoriteCompanies[i]) {
                sets[i].insert(company);
            }
        }
        
        for (int i = 0; i < n; i++) {
            bool isSubset = false;
            for (int j = 0; j < n; j++) {
                if (i != j && sets[i].size() <= sets[j].size()) {
                    bool allFound = true;
                    for (const string& company : favoriteCompanies[i]) {
                        if (sets[j].find(company) == sets[j].end()) {
                            allFound = false;
                            break;
                        }
                    }
                    if (allFound) {
                        isSubset = true;
                        break;
                    }
                }
            }
            if (!isSubset) {
                result.push_back(i);
            }
        }
        
        return result;
    }
}; 