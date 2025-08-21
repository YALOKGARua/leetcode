#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

int main() {
    vector<string> g(15);
    for (int i = 0; i < 15; i++) getline(cin, g[i]);

    int ballX = -1, ballY = -1;
    char ballChar = 0;
    vector<int> ax;
    vector<int> bx;
    vector<pair<int,int>> aPos;
    vector<pair<int,int>> bPos;
    for (int y = 0; y < 15; y++) {
        for (int x = 0; x < 51; x++) {
            char c = g[y][x];
            if (c == 'o' || c == 'O') { ballX = x; ballY = y; ballChar = c; }
            if (c == 'a' || c == 'A') { ax.push_back(x); aPos.push_back({y,x}); }
            if (c == 'b' || c == 'B') { bx.push_back(x); bPos.push_back({y,x}); }
        }
    }

    bool throwIn = (ballY == 0 || ballY == 14);
    if (throwIn || ballChar == 0) {
        cout << "No player in an offside position." << endl;
        cout << "VAR: ONSIDE!" << endl;
        return 0;
    }

    bool teamAAttacks = (ballChar == 'o');

    int secondOpp = -1;
    if (teamAAttacks) {
        if ((int)bx.size() >= 2) {
            int first = numeric_limits<int>::max();
            int second = numeric_limits<int>::max();
            for (int x : bx) {
                if (x < first) { second = first; first = x; }
                else if (x < second) { second = x; }
            }
            secondOpp = second;
        } else {
            secondOpp = -1;
        }
    } else {
        if ((int)ax.size() >= 2) {
            int first = numeric_limits<int>::min();
            int second = numeric_limits<int>::min();
            for (int x : ax) {
                if (x > first) { second = first; first = x; }
                else if (x > second) { second = x; }
            }
            secondOpp = second;
        } else {
            secondOpp = 51;
        }
    }

    int offsideCount = 0;
    bool offence = false;
    if (teamAAttacks) {
        for (auto [y,x] : aPos) {
            if (x >= 25) continue;
            if (secondOpp == -1) continue;
            if (x < ballX && x < secondOpp) {
                offsideCount++;
                if (g[y][x] == 'A') offence = true;
            }
        }
    } else {
        for (auto [y,x] : bPos) {
            if (x <= 25) continue;
            if (secondOpp == 51) continue;
            if (x > ballX && x > secondOpp) {
                offsideCount++;
                if (g[y][x] == 'B') offence = true;
            }
        }
    }

    if (offsideCount == 0) cout << "No player in an offside position." << endl;
    else cout << offsideCount << " player(s) in an offside position." << endl;
    cout << (offence ? "VAR: OFFSIDE!" : "VAR: ONSIDE!") << endl;
}