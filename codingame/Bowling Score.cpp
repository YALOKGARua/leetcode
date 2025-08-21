#include <iostream>
#include <string>
#include <vector>

using namespace std;

static int charPins(char c) {
    if (c == 'X') return 10;
    if (c == '-') return 0;
    if (c >= '0' && c <= '9') return c - '0';
    return 0;
}

int main() {
    int n;
    cin >> n; cin.ignore();
    for (int g = 0; g < n; g++) {
        string line;
        getline(cin, line);
        vector<string> frames;
        string cur;
        for (char c : line) {
            if (c == ' ') {
                if (!cur.empty()) { frames.push_back(cur); cur.clear(); }
            } else {
                cur.push_back(c);
            }
        }
        if (!cur.empty()) frames.push_back(cur);

        vector<int> rolls;
        for (int i = 0; i < 9; i++) {
            const string& f = frames[i];
            if (f.size() == 1 && f[0] == 'X') {
                rolls.push_back(10);
            } else {
                int first = charPins(f[0]);
                int second = (f[1] == '/') ? (10 - first) : charPins(f[1]);
                rolls.push_back(first);
                rolls.push_back(second);
            }
        }
        const string& f10 = frames[9];
        for (int i = 0; i < (int)f10.size(); i++) {
            char c = f10[i];
            if (c == '/') {
                int prev = rolls.back();
                rolls.push_back(10 - prev);
            } else {
                rolls.push_back(charPins(c));
            }
        }

        vector<int> out;
        out.reserve(10);
        int total = 0;
        int ri = 0;
        for (int frame = 0; frame < 10; frame++) {
            if (rolls[ri] == 10) {
                int score = 10 + rolls[ri + 1] + rolls[ri + 2];
                total += score;
                out.push_back(total);
                ri += 1;
            } else {
                int first = rolls[ri];
                int second = rolls[ri + 1];
                if (first + second == 10) {
                    int score = 10 + rolls[ri + 2];
                    total += score;
                    out.push_back(total);
                } else {
                    int score = first + second;
                    total += score;
                    out.push_back(total);
                }
                ri += 2;
            }
        }

        for (int i = 0; i < 10; i++) {
            if (i) cout << ' ';
            cout << out[i];
        }
        cout << "\n";
    }
}