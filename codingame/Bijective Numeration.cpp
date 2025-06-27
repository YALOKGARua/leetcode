#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long decimaryToDecimal(const string& decimary) {
    long long result = 0;
    long long power = 1;
    
    for (int i = decimary.length() - 1; i >= 0; i--) {
        char digit = decimary[i];
        long long value = (digit == 'A') ? 10 : (digit - '0');
        result += value * power;
        power *= 10;
    }
    
    return result;
}

string decimalToDecimary(long long decimal) {
    if (decimal == 0) return "";
    
    string result = "";
    
    while (decimal > 0) {
        long long remainder = decimal % 10;
        if (remainder == 0) {
            remainder = 10;
            decimal = (decimal / 10) - 1;
        } else {
            decimal = decimal / 10;
        }
        
        if (remainder == 10) {
            result = 'A' + result;
        } else {
            result = char('0' + remainder) + result;
        }
    }
    
    return result;
}

int main() {
    int count;
    cin >> count;
    cin.ignore();
    
    vector<string> decimaries;
    for (int i = 0; i < count; i++) {
        string decimary;
        cin >> decimary;
        decimaries.push_back(decimary);
    }
    cin.ignore();
    
    long long sum = 0;
    for (const string& decimary : decimaries) {
        sum += decimaryToDecimal(decimary);
    }
    
    cout << decimalToDecimary(sum) << endl;
    
    return 0;
}
