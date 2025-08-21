#include <iostream>
#include <string>
#include <vector>

using namespace std;

static bool isWin(const vector<string>& b) {
    for (int i = 0; i < 3; i++) {
        if (b[i][0] == 'O' && b[i][1] == 'O' && b[i][2] == 'O') return true;
        if (b[0][i] == 'O' && b[1][i] == 'O' && b[2][i] == 'O') return true;
    }
    if (b[0][0] == 'O' && b[1][1] == 'O' && b[2][2] == 'O') return true;
    if (b[0][2] == 'O' && b[1][1] == 'O' && b[2][0] == 'O') return true;
    return false;
}

int main() {
    vector<string> b(3);
    for (int i = 0; i < 3; i++) getline(cin, b[i]);
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (b[r][c] != '.') continue;
            b[r][c] = 'O';
            if (isWin(b)) {
                cout << b[0] << "\n" << b[1] << "\n" << b[2] << "\n";
                return 0;
            }
            b[r][c] = '.';
        }
    }
    cout << "false\n";
}