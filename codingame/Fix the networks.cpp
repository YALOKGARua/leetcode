#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

uint32_t parseIP(const string& ip) {
    istringstream iss(ip);
    string segment;
    uint32_t result = 0;
    int shift = 24;
    
    while (getline(iss, segment, '.')) {
        result |= (stoi(segment) << shift);
        shift -= 8;
    }
    
    return result;
}

string formatIP(uint32_t ip) {
    return to_string((ip >> 24) & 0xFF) + "." +
           to_string((ip >> 16) & 0xFF) + "." +
           to_string((ip >> 8) & 0xFF) + "." +
           to_string(ip & 0xFF);
}

int countTrailingZeros(uint32_t n) {
    if (n == 0) return 32;
    int count = 0;
    while ((n & 1) == 0) {
        n >>= 1;
        count++;
    }
    return count;
}

bool isValidCIDR(uint32_t ip, int prefixLength) {
    int variableBits = 32 - prefixLength;
    if (variableBits == 0) return true;
    
    uint32_t mask = (1ULL << variableBits) - 1;
    return (ip & mask) == 0;
}

long long calculateAddresses(int prefixLength) {
    return 1LL << (32 - prefixLength);
}

int findMaxValidPrefixLength(uint32_t ip) {
    int trailingZeros = countTrailingZeros(ip);
    return 32 - trailingZeros;
}

int main() {
    int m;
    cin >> m;
    cin.ignore();
    
    for (int i = 0; i < m; i++) {
        string cidr;
        getline(cin, cidr);
        
        size_t slashPos = cidr.find('/');
        string ipStr = cidr.substr(0, slashPos);
        int prefixLength = stoi(cidr.substr(slashPos + 1));
        
        uint32_t ip = parseIP(ipStr);
        
        if (isValidCIDR(ip, prefixLength)) {
            long long addresses = calculateAddresses(prefixLength);
            cout << "valid " << addresses << endl;
        } else {
            int maxValidPrefix = findMaxValidPrefixLength(ip);
            long long addresses = calculateAddresses(maxValidPrefix);
            cout << "invalid " << formatIP(ip) << "/" << maxValidPrefix 
                 << " " << addresses << endl;
        }
    }
    
    return 0;
}
