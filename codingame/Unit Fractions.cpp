#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    long long n;
    cin >> n;
    cin.ignore();
    
    vector<pair<long long, long long>> solutions;
    
    for (long long d = 1; d * d <= n * n; d++) {
        if ((n * n) % d == 0) {
            long long d1 = d;
            long long d2 = (n * n) / d;
            
            long long x = d1 + n;
            long long y = d2 + n;
            
            if (x >= y) {
                solutions.push_back({x, y});
            }
            
            if (d1 != d2) {
                x = d2 + n;
                y = d1 + n;
                if (x >= y) {
                    solutions.push_back({x, y});
                }
            }
        }
    }
    
    sort(solutions.begin(), solutions.end(), greater<pair<long long, long long>>());
    
    for (const auto& sol : solutions) {
        cout << "1/" << n << " = 1/" << sol.first << " + 1/" << sol.second << endl;
    }
    
    return 0;
}
