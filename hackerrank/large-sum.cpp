#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

string addStrings(string a, string b) {
    string result = "";
    int carry = 0;
    int i = a.length() - 1;
    int j = b.length() - 1;
    
    while(i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if(i >= 0) sum += a[i] - '0';
        if(j >= 0) sum += b[j] - '0';
        
        result = char(sum % 10 + '0') + result;
        carry = sum / 10;
        i--;
        j--;
    }
    
    return result;
}

int main() {
    int n;
    cin >> n;
    
    string sum = "0";
    
    for(int i = 0; i < n; i++) {
        string num;
        cin >> num;
        sum = addStrings(sum, num);
    }
    
    cout << sum.substr(0, 10) << endl;
    
    return 0;
} 