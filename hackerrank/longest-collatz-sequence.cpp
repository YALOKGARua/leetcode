#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<int> memo(5000001, -1);
vector<int> best(5000001, 0);

int collatzLength(long long n) {
    if(n <= 5000000 && memo[n] != -1) {
        return memo[n];
    }
    
    int length = 1;
    long long original = n;
    
    while(n != 1) {
        if(n % 2 == 0) {
            n /= 2;
        } else {
            n = 3 * n + 1;
        }
        length++;
        
        if(n <= 5000000 && memo[n] != -1) {
            length += memo[n] - 1;
            break;
        }
    }
    
    if(original <= 5000000) {
        memo[original] = length;
    }
    
    return length;
}

int main() {
    memo[1] = 1;
    
    int maxLength = 0;
    int bestNum = 1;
    
    for(int i = 1; i <= 5000000; i++) {
        int length = collatzLength(i);
        if(length >= maxLength) {
            maxLength = length;
            bestNum = i;
        }
        best[i] = bestNum;
    }
    
    int t;
    cin >> t;
    
    for(int test = 0; test < t; test++) {
        int n;
        cin >> n;
        cout << best[n] << endl;
    }
    
    return 0;
} 