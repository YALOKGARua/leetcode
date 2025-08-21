#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string s;
    getline(cin, s);
    vector<int> b(16);
    for (int i = 0; i < 16; i++) b[i] = s[i] - '0';

    auto parity = [&](const vector<int>& idx) {
        int sum = 0;
        for (int v : idx) sum ^= b[v];
        return sum;
    };

    vector<int> setB = {1,3,5,7,9,11,13,15};
    vector<int> setC = {2,3,6,7,10,11,14,15};
    vector<int> setE = {4,5,6,7,12,13,14,15};
    vector<int> setI = {8,9,10,11,12,13,14,15};

    int errB = parity(setB);
    int errC = parity(setC);
    int errE = parity(setE);
    int errI = parity(setI);

    int total = 0;
    for (int i = 0; i < 16; i++) total ^= b[i];
    bool globalEven = (total == 0);

    if (errB == 0 && errC == 0 && errE == 0 && errI == 0) {
        if (globalEven) {
            cout << s << "\n";
            return 0;
        } else {
            b[0] ^= 1;
            for (int i = 0; i < 16; i++) s[i] = char('0' + b[i]);
            cout << s << "\n";
            return 0;
        }
    }

    if (globalEven) {
        cout << "TWO ERRORS\n";
        return 0;
    }

    int cand = -1;
    for (int i = 1; i < 16; i++) {
        int inB = 0, inC = 0, inE = 0, inI = 0;
        for (int v : setB) if (v == i) inB = 1;
        for (int v : setC) if (v == i) inC = 1;
        for (int v : setE) if (v == i) inE = 1;
        for (int v : setI) if (v == i) inI = 1;
        if (inB == errB && inC == errC && inE == errE && inI == errI) { cand = i; break; }
    }

    if (cand == -1) {
        cout << "TWO ERRORS\n";
        return 0;
    }

    b[cand] ^= 1;
    for (int i = 0; i < 16; i++) s[i] = char('0' + b[i]);
    cout << s << "\n";
}