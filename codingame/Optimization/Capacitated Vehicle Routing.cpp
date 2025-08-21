#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

struct Node { int idx; int x; int y; int d; };

static inline int distRound(const Node& a, const Node& b) {
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;
    return (int)llround(sqrt((double)(dx * dx + dy * dy)));
}

static int routeCost(const vector<int>& r, const vector<vector<int>>& D) {
    int cost = 0;
    int prev = 0;
    for (int v : r) { cost += D[prev][v]; prev = v; }
    cost += D[prev][0];
    return cost;
}

static bool twoOptImprove(vector<int>& r, const vector<vector<int>>& D) {
    int m = (int)r.size();
    if (m < 3) return false;
    int bestDelta = 0;
    int bi = -1, bj = -1;
    for (int i = 0; i < m - 1; i++) {
        int a = (i == 0) ? 0 : r[i - 1];
        int b = r[i];
        for (int j = i + 1; j < m; j++) {
            int c = r[j];
            int d = (j == m - 1) ? 0 : r[j + 1];
            int before = D[a][b] + D[c][d];
            int after = D[a][c] + D[b][d];
            int delta = after - before;
            if (delta < bestDelta) { bestDelta = delta; bi = i; bj = j; }
        }
    }
    if (bestDelta < 0) {
        reverse(r.begin() + bi, r.begin() + bj + 1);
        return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    int cap;
    cin >> cap;
    vector<Node> nodes(n);
    for (int i = 0; i < n; i++) {
        cin >> nodes[i].idx >> nodes[i].x >> nodes[i].y >> nodes[i].d;
    }
    vector<vector<int>> D(n, vector<int>(n));
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) D[i][j] = distRound(nodes[i], nodes[j]);

    vector<vector<int>> routes;
    vector<int> routeDemand;
    vector<int> whichRoute(n, -1);
    for (int i = 1; i < n; i++) {
        routes.push_back({i});
        routeDemand.push_back(nodes[i].d);
        whichRoute[i] = (int)routes.size() - 1;
    }

    struct Saving { int i, j, s; };
    vector<Saving> S;
    S.reserve((n - 1) * (n - 2) / 2);
    for (int i = 1; i < n; i++) for (int j = i + 1; j < n; j++) S.push_back({i, j, D[0][i] + D[0][j] - D[i][j]});
    sort(S.begin(), S.end(), [](const Saving& a, const Saving& b){ return a.s > b.s; });

    for (const auto& sv : S) {
        int i = sv.i, j = sv.j;
        int ri = whichRoute[i];
        int rj = whichRoute[j];
        if (ri == -1 || rj == -1 || ri == rj) continue;
        auto& A = routes[ri];
        auto& B = routes[rj];
        int di = routeDemand[ri];
        int dj = routeDemand[rj];
        if (di + dj > cap) continue;
        bool iFront = (A.front() == i);
        bool iBack = (A.back() == i);
        bool jFront = (B.front() == j);
        bool jBack = (B.back() == j);
        if (!(iFront || iBack) || !(jFront || jBack)) continue;
        if (iBack && jFront) {
            A.insert(A.end(), B.begin(), B.end());
        } else if (iFront && jBack) {
            B.insert(B.end(), A.begin(), A.end());
            routes[ri].clear();
            routes[ri].shrink_to_fit();
            whichRoute[i] = -1;
            for (int v : B) whichRoute[v] = rj;
            routeDemand[rj] = di + dj;
            continue;
        } else if (iFront && jFront) {
            reverse(A.begin(), A.end());
            A.insert(A.end(), B.begin(), B.end());
        } else if (iBack && jBack) {
            reverse(B.begin(), B.end());
            A.insert(A.end(), B.begin(), B.end());
        } else {
            continue;
        }
        for (int v : B) whichRoute[v] = ri;
        routes[rj].clear();
        routes[rj].shrink_to_fit();
        routeDemand[ri] = di + dj;
        routeDemand[rj] = 0;
    }

    vector<vector<int>> finalRoutes;
    finalRoutes.reserve(routes.size());
    for (auto& r : routes) if (!r.empty()) finalRoutes.push_back(r);

    for (auto& r : finalRoutes) {
        bool improved = true;
        int it = 0;
        while (improved && it < 50) { improved = twoOptImprove(r, D); it++; }
    }

    for (int i = 0; i < (int)finalRoutes.size(); i++) {
        if (i) cout << ';';
        for (int j = 0; j < (int)finalRoutes[i].size(); j++) {
            if (j) cout << ' ';
            cout << finalRoutes[i][j];
        }
    }
    cout << "\n";
}