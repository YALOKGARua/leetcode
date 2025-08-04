#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int countDivisors(long long n) {
    int count = 1;
    for(int i = 2; i * i <= n; i++) {
        int power = 0;
        while(n % i == 0) {
            power++;
            n /= i;
        }
        count *= (power + 1);
    }
    if(n > 1) {
        count *= 2;
    }
    return count;
}

int main() {
    int t;
    cin >> t;
    
    for(int test = 0; test < t; test++) {
        int n;
        cin >> n;
        
        long long triangle = 1;
        long long i = 2;
        
        while(countDivisors(triangle) <= n) {
            triangle += i;
            i++;
        }
        
        cout << triangle << endl;
    }
    
    return 0;
} 