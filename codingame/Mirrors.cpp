#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int main() {
    int n;
    if (!(cin >> n)) return 0;
    vector<double> r(n);
    for (int i = 0; i < n; ++i) cin >> r[i];

    const double EPS = 1e-12;
    double R = 0.0;
    for (int i = n - 1; i >= 0; --i) {
        double ri = r[i];
        if (ri >= 1.0 - EPS) {
            R = 1.0;
            continue;
        }
        double t = 1.0 - ri;
        double denom = 1.0 - ri * R;
        if (denom <= EPS) {
            R = 1.0;
        } else {
            R = ri + (t * t * R) / denom;
            if (R < 0.0) R = 0.0;
            if (R > 1.0) R = 1.0;
        }
    }

    cout << fixed << setprecision(4) << R << endl;
    return 0;
}