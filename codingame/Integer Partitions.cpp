#include <iostream>
#include <vector>

using namespace std;

static void dfs(int rem, int maxNext, vector<int>& cur) {
    if (rem == 0) {
        for (int i = 0; i < (int)cur.size(); i++) {
            if (i) cout << ' ';
            cout << cur[i];
        }
        cout << "\n";
        return;
    }
    int upper = maxNext < rem ? maxNext : rem;
    for (int k = upper; k >= 1; k--) {
        cur.push_back(k);
        dfs(rem - k, k, cur);
        cur.pop_back();
    }
}

int main() {
    int n;
    if (!(cin >> n)) return 0;
    vector<int> cur;
    dfs(n, n, cur);
}