#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; long long m; cin >> n >> m;
        vector<long long> a(n);
        for (auto &x : a) cin >> x;
        set<long long> s;
        long long sum = 0, res = 0;
        s.insert(0);
        for (auto x : a) {
            sum = (sum + x) % m;
            res = max(res, sum);
            auto it = s.upper_bound(sum);
            if (it != s.end()) res = max(res, (sum - *it + m) % m);
            s.insert(sum);
        }
        cout << res << '\n';
    }
    return 0;
} 