#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    int l;
    cin >> l; cin.ignore();
    int w;
    cin >> w; cin.ignore();
    int d;
    cin >> d; cin.ignore();
    int n;
    cin >> n; cin.ignore();
    vector<vector<string>> grid(d, vector<string>(w, string(l, '.')));
    int z = 0;
    int y = 0;
    for (int i = 0; i < n; i++) {
        string s;
        getline(cin, s);
        if (s.empty()) continue;
        if ((int)s.size() < l) s += string(l - (int)s.size(), '.');
        grid[z][y] = s.substr(0, l);
        y++;
        if (y == w) {
            y = 0;
            if (z + 1 < d) z++;
        }
    }

    struct Source { int x; int y; int z; int r; };
    vector<Source> sources;
    for (int zz = 0; zz < d; zz++) {
        for (int yy = 0; yy < w; yy++) {
            for (int xx = 0; xx < l; xx++) {
                char c = grid[zz][yy][xx];
                if (c == '.') continue;
                int r = 0;
                if (c >= '1' && c <= '9') r = c - '0';
                else if (c >= 'A' && c <= 'Z') r = 10 + (c - 'A');
                if (r > 0) sources.push_back({xx, yy, zz, r});
            }
        }
    }

    vector<vector<vector<int>>> brightness(d, vector<vector<int>>(w, vector<int>(l, 0)));
    for (const auto& src : sources) {
        for (int zz = 0; zz < d; zz++) {
            for (int yy = 0; yy < w; yy++) {
                for (int xx = 0; xx < l; xx++) {
                    int dx = xx - src.x;
                    int dy = yy - src.y;
                    int dz = zz - src.z;
                    double dist = sqrt((double)(dx * dx + dy * dy + dz * dz));
                    int rd = (int)llround(dist);
                    int contrib = src.r - rd;
                    if (contrib > 0) brightness[zz][yy][xx] += contrib;
                }
            }
        }
    }

    auto mapChar = [](int v) -> char {
        if (v <= 0) return '0';
        if (v <= 9) return (char)('0' + v);
        if (v <= 35) return (char)('A' + (v - 10));
        return 'Z';
    };

    for (int zz = 0; zz < d; zz++) {
        for (int yy = 0; yy < w; yy++) {
            string line;
            line.resize(l);
            for (int xx = 0; xx < l; xx++) line[xx] = mapChar(brightness[zz][yy][xx]);
            cout << line << endl;
        }
        if (zz + 1 < d) cout << endl;
    }
}