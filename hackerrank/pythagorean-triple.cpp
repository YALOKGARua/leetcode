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

int main(){
    int t;
    cin >> t;
    for(int a0 = 0; a0 < t; a0++){
        int n;
        cin >> n;
        
        long long maxProduct = -1;
        
        for(int m = 2; m * m <= n; m++){
            for(int k = 1; k < m; k++){
                if(__gcd(m, k) == 1 && (m - k) % 2 == 1){
                    int a = m*m - k*k;
                    int b = 2*m*k;
                    int c = m*m + k*k;
                    
                    if(a + b + c <= n && n % (a + b + c) == 0){
                        int factor = n / (a + b + c);
                        long long product = (long long)(a * factor) * (b * factor) * (c * factor);
                        maxProduct = max(maxProduct, product);
                    }
                }
            }
        }
        
        cout << maxProduct << endl;
    }
    return 0;
} 