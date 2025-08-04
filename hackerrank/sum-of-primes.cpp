#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

vector<long long> sieve(int n) {
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    
    for(int i = 2; i * i <= n; i++) {
        if(isPrime[i]) {
            for(int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    
    vector<long long> primes;
    for(int i = 2; i <= n; i++) {
        if(isPrime[i]) {
            primes.push_back(i);
        }
    }
    
    return primes;
}

int main(){
    int t;
    cin >> t;
    
    vector<int> queries;
    int maxN = 0;
    
    for(int a0 = 0; a0 < t; a0++){
        int n;
        cin >> n;
        queries.push_back(n);
        maxN = max(maxN, n);
    }
    
    vector<long long> primes = sieve(maxN);
    vector<long long> prefixSum(maxN + 1, 0);
    
    int primeIndex = 0;
    for(int i = 2; i <= maxN; i++) {
        if(primeIndex < primes.size() && primes[primeIndex] == i) {
            prefixSum[i] = prefixSum[i-1] + i;
            primeIndex++;
        } else {
            prefixSum[i] = prefixSum[i-1];
        }
    }
    
    for(int n : queries) {
        cout << prefixSum[n] << endl;
    }
    
    return 0;
} 