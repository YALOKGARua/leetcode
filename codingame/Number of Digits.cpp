#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

long long countDigitInRange(int n, int k) {
    if (n < 0) return 0;
    
    long long count = 0;
    long long factor = 1;
    
    while (factor <= n) {
        long long higher = n / (factor * 10);
        long long cur = (n / factor) % 10;
        long long lower = n % factor;
        
        if (k == 0) {
            if (higher == 0) break;
            if (cur == 0) {
                count += (higher - 1) * factor + lower + 1;
            } else {
                count += (higher - 1) * factor;
            }
        } else {
            if (cur < k) {
                count += higher * factor;
            } else if (cur == k) {
                count += higher * factor + lower + 1;
            } else {
                count += (higher + 1) * factor;
            }
        }
        
        factor *= 10;
    }
    
    return count;
}

int main() {
    int n, k;
    cin >> n;
    cin.ignore();
    cin >> k;
    cin.ignore();
    
    cout << countDigitInRange(n, k) << endl;
    
    return 0;
}
