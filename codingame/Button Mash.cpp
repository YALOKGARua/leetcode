#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

unordered_map<int, int> memo;

int solve(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    
    if (memo.count(n)) return memo[n];
    
    int result;
    if (n % 2 == 0) {
        result = 1 + solve(n / 2);
    } else {
        result = 1 + min(solve(n - 1), solve(n + 1));
    }
    
    return memo[n] = result;
}

int main() {
    int n;
    cin >> n;
    cin.ignore();
    
    cout << solve(n) << endl;
    
    return 0;
}
