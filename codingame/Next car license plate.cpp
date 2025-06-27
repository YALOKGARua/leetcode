#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string x;
    getline(cin, x);
    int n;
    cin >> n;
    cin.ignore();
    
    string prefix = x.substr(0, 2);
    int number = stoi(x.substr(3, 3));
    string suffix = x.substr(7, 2);
    
    long long totalSteps = n;
    
    number += totalSteps;
    
    while (number > 999) {
        number -= 999;
        
        int suffixValue = (suffix[0] - 'A') * 26 + (suffix[1] - 'A');
        suffixValue++;
        
        if (suffixValue >= 676) {
            suffixValue = 0;
            
            int prefixValue = (prefix[0] - 'A') * 26 + (prefix[1] - 'A');
            prefixValue++;
            
            prefix[0] = 'A' + (prefixValue / 26);
            prefix[1] = 'A' + (prefixValue % 26);
        }
        
        suffix[0] = 'A' + (suffixValue / 26);
        suffix[1] = 'A' + (suffixValue % 26);
    }
    
    string result = prefix + "-";
    if (number < 10) result += "00";
    else if (number < 100) result += "0";
    result += to_string(number);
    result += "-" + suffix;
    
    cout << result << endl;
    
    return 0;
}
