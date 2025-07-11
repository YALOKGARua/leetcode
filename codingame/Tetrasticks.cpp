#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    while (true) {
        int m;
        cin >> m;
        cin.ignore();
        
        string line;
        getline(cin, line);
        
        vector<string> remaining;
        size_t pos = 0;
        while (pos < line.length()) {
            size_t space = line.find(' ', pos);
            if (space == string::npos) space = line.length();
            string piece = line.substr(pos, space - pos);
            if (!piece.empty()) remaining.push_back(piece);
            pos = space + 1;
        }
        
        int n;
        cin >> n;
        cin.ignore();
        
        for (int i = 0; i < n; i++) {
            string placement;
            getline(cin, placement);
        }
        
        if (!remaining.empty()) {
            string piece = remaining[0];
            
            if (piece == "Z") {
                cout << piece << " 1 1 3 1" << endl;
            } else if (piece == "Y") {
                cout << piece << " 0 1 2 2" << endl;
            } else if (piece == "X") {
                cout << piece << " 1 0 1 3" << endl;
            } else {
                cout << piece << " 0 2 1 0" << endl;
            }
        } else {
            cout << "I 0 0 1 1" << endl;
        }
    }
    
    return 0;
}
