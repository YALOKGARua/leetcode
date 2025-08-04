#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() {
    int x, n;
    cin >> x >> n;
    vector<int> bricks(n);
    for (int& m : bricks) cin >> m;
    sort(bricks.rbegin(), bricks.rend());
    vector<int> row_sizes;
    int left = n;
    while (left > 0) {
        int sz = min(x, left);
        row_sizes.push_back(sz);
        left -= sz;
        x = sz;
    }
    double work = 0;
    int idx = 0;
    for (int l = 0; l < row_sizes.size(); ++l) {
        for (int j = 0; j < row_sizes[l]; ++j, ++idx) {
            work += l * 6.5 / 100 * 10 * bricks[idx];
        }
    }
    cout << fixed << setprecision(3) << work << endl;
}
