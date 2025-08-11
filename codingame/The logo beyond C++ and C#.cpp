#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int size; if (!(cin >> size)) return 0; cin.ignore();
    int thickness; cin >> thickness; cin.ignore();
    int n; cin >> n; cin.ignore();
    vector<string> rows(n);
    int m = 0;
    for (int i = 0; i < n; i++) { getline(cin, rows[i]); m = max(m, (int)rows[i].size()); }
    int H = size * n;
    int W = size * m;
    if (H == 0 || W == 0) return 0;
    vector<vector<unsigned char>> filled(H, vector<unsigned char>(W, 0));
    int bandStart = (size - thickness) / 2;
    int bandEnd = bandStart + thickness - 1;
    for (int r = 0; r < n; r++) {
        const string& line = rows[r];
        for (int c = 0; c < (int)line.size(); c++) {
            if (line[c] != '+') continue;
            int y0 = r * size;
            int x0 = c * size;
            for (int y = 0; y < size; y++) {
                for (int x = bandStart; x <= bandEnd; x++) filled[y0 + y][x0 + x] = 1;
            }
            for (int y = bandStart; y <= bandEnd; y++) {
                for (int x = 0; x < size; x++) filled[y0 + y][x0 + x] = 1;
            }
        }
    }
    string out;
    out.reserve(W);
    for (int y = 0; y < H; y++) {
        out.clear();
        for (int x = 0; x < W; x++) {
            if (!filled[y][x]) { out.push_back(' '); continue; }
            bool b = false;
            if (y == 0 || !filled[y - 1][x]) b = true;
            else if (y == H - 1 || !filled[y + 1][x]) b = true;
            else if (x == 0 || !filled[y][x - 1]) b = true;
            else if (x == W - 1 || !filled[y][x + 1]) b = true;
            else {
                if (y > 0 && x > 0 && !filled[y - 1][x - 1] && filled[y - 1][x] && filled[y][x - 1]) b = true;
                else if (y > 0 && x + 1 < W && !filled[y - 1][x + 1] && filled[y - 1][x] && filled[y][x + 1]) b = true;
                else if (y + 1 < H && x > 0 && !filled[y + 1][x - 1] && filled[y + 1][x] && filled[y][x - 1]) b = true;
                else if (y + 1 < H && x + 1 < W && !filled[y + 1][x + 1] && filled[y + 1][x] && filled[y][x + 1]) b = true;
            }
            out.push_back(b ? '+' : ' ');
        }
        int last = (int)out.find_last_not_of(' ');
        if (last == -1) cout << "" << '\n';
        else cout << out.substr(0, last + 1) << '\n';
    }
    return 0;
}