#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class GiftCostDistributor {
private:
    vector<long long> budgets;
    long long totalCost;
    int participantsCount;
    
    bool canAffordGift() const {
        long long totalBudget = accumulate(budgets.begin(), budgets.end(), 0LL);
        return totalBudget >= totalCost;
    }
    
    vector<long long> calculateOptimalContributions() {
        vector<long long> sortedBudgets = budgets;
        sort(sortedBudgets.begin(), sortedBudgets.end());
        
        vector<long long> contributions(participantsCount);
        long long remainingCost = totalCost;
        
        for (int i = 0; i < participantsCount; i++) {
            int remainingParticipants = participantsCount - i;
            long long equalShare = remainingCost / remainingParticipants;
            long long remainder = remainingCost % remainingParticipants;
            
            long long baseContribution = min(equalShare, sortedBudgets[i]);
            contributions[i] = baseContribution;
            remainingCost -= baseContribution;
        }
        
        for (int i = participantsCount - 1; i >= 0 && remainingCost > 0; i--) {
            long long additionalCapacity = sortedBudgets[i] - contributions[i];
            long long toAdd = min(remainingCost, additionalCapacity);
            contributions[i] += toAdd;
            remainingCost -= toAdd;
        }
        
        sort(contributions.begin(), contributions.end());
        return contributions;
    }
    
public:
    GiftCostDistributor(int n, long long cost, const vector<long long>& participantBudgets) 
        : participantsCount(n), totalCost(cost), budgets(participantBudgets) {}
    
    void processAndPrintResult() {
        if (!canAffordGift()) {
            cout << "IMPOSSIBLE" << endl;
            return;
        }
        
        vector<long long> contributions = calculateOptimalContributions();
        
        for (long long contribution : contributions) {
            cout << contribution << endl;
        }
    }
};

int main() {
    int n;
    long long c;
    cin >> n >> c;
    
    vector<long long> budgets(n);
    for (int i = 0; i < n; i++) {
        cin >> budgets[i];
    }
    
    GiftCostDistributor distributor(n, c, budgets);
    distributor.processAndPrintResult();
    
    return 0;
}