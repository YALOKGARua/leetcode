#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <chrono>
using namespace std;

struct Move { int x; int y; char dir; char op; };

static inline int idx(int x, int y, int w) { return y * w + x; }

static uint64_t hashGrid(const vector<int>& g) {
    uint64_t h = 1469598103934665603ull;
    for (size_t i = 0; i < g.size(); i++) {
        uint64_t v = (uint64_t)g[i];
        uint64_t z = (uint64_t)(i + 0x9e3779b97f4a7c15ull) ^ (v * 0x9e3779b97f4a7c15ull);
        h ^= z;
        h *= 1099511628211ull;
    }
    return h;
}

static void genMoves(const vector<int>& grid, int w, int h, vector<Move>& out) {
    out.clear();
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            int v = grid[idx(x, y, w)];
            if (v <= 0) continue;
            int tx = x + v; if (tx < w && grid[idx(tx, y, w)] != 0) { out.push_back({x, y, 'R', '+'}); out.push_back({x, y, 'R', '-'}); }
            tx = x - v; if (tx >= 0 && grid[idx(tx, y, w)] != 0) { out.push_back({x, y, 'L', '+'}); out.push_back({x, y, 'L', '-'}); }
            int ty = y + v; if (ty < h && grid[idx(x, ty, w)] != 0) { out.push_back({x, y, 'D', '+'}); out.push_back({x, y, 'D', '-'}); }
            ty = y - v; if (ty >= 0 && grid[idx(x, ty, w)] != 0) { out.push_back({x, y, 'U', '+'}); out.push_back({x, y, 'U', '-'}); }
        }
    }
}

static bool apply(const Move& m, vector<int>& grid, int w, int h, int& nonzero, int& sx, int& sy, int& dx, int& dy, int& oldS, int& oldD, int& newD) {
    sx = m.x; sy = m.y; int v = grid[idx(sx, sy, w)]; if (v <= 0) return false;
    if (m.dir == 'R') { dx = sx + v; dy = sy; }
    else if (m.dir == 'L') { dx = sx - v; dy = sy; }
    else if (m.dir == 'D') { dx = sx; dy = sy + v; }
    else { dx = sx; dy = sy - v; }
    if (dx < 0 || dx >= w || dy < 0 || dy >= h) return false;
    int di = idx(dx, dy, w);
    if (grid[di] == 0) return false;
    oldS = v; oldD = grid[di];
    newD = (m.op == '+') ? oldD + oldS : abs(oldD - oldS);
    grid[idx(sx, sy, w)] = 0;
    grid[di] = newD;
    if (oldS > 0) nonzero--;
    if (oldD > 0 && newD == 0) nonzero--;
    return true;
}

static void undo(vector<int>& grid, int w, int sx, int sy, int dx, int dy, int& nonzero, int oldS, int oldD, int newD) {
    if (oldS > 0) nonzero++;
    if (oldD > 0 && newD == 0) nonzero++;
    grid[idx(sx, sy, w)] = oldS;
    grid[idx(dx, dy, w)] = oldD;
}

static int heuristic(int nonzero) {
    if (nonzero <= 0) return 0;
    return (nonzero + 1) / 2;
}

static int ida(vector<int>& grid, int w, int h, int nonzero, int g, int bound, vector<Move>& path, unordered_set<uint64_t>& seen, chrono::steady_clock::time_point deadline) {
    if (nonzero == 0) return -1;
    if (chrono::steady_clock::now() > deadline) return 1e9;
    int f = g + heuristic(nonzero);
    if (f > bound) return f;
    uint64_t key = hashGrid(grid);
    if (seen.find(key) != seen.end()) return 1e9;
    seen.insert(key);
    vector<Move> moves;
    genMoves(grid, w, h, moves);
    struct Scored { int score; Move m; int newVal; int nzDec; };
    vector<Scored> cand;
    cand.reserve(moves.size());
    for (const auto& m : moves) {
        int sx, sy, dx, dy, os, od, nd; int nz = nonzero;
        if (!apply(m, grid, w, h, nz, sx, sy, dx, dy, os, od, nd)) continue;
        int dec = (os > 0 ? 1 : 0) + ((od > 0 && nd == 0) ? 1 : 0);
        int sc = dec * 100000 - nd;
        cand.push_back({sc, m, nd, dec});
        undo(grid, w, sx, sy, dx, dy, nz, os, od, nd);
    }
    sort(cand.begin(), cand.end(), [](const Scored& a, const Scored& b){ return a.score > b.score; });
    int minNext = 1e9;
    for (const auto& c : cand) {
        int sx, sy, dx, dy, os, od, nd; int nz = nonzero;
        if (!apply(c.m, grid, w, h, nz, sx, sy, dx, dy, os, od, nd)) continue;
        path.push_back(c.m);
        int t = ida(grid, w, h, nz, g + 1, bound, path, seen, deadline);
        if (t == -1) return -1;
        if (t < minNext) minNext = t;
        path.pop_back();
        undo(grid, w, sx, sy, dx, dy, nz, os, od, nd);
        if (chrono::steady_clock::now() > deadline) { seen.erase(key); return 1e9; }
    }
    seen.erase(key);
    return minNext;
}

static bool idaDfs(vector<int>& grid, int w, int h, int nonzero, int g, int bound, vector<Move>& path, unordered_set<uint64_t>& seen, chrono::steady_clock::time_point deadline) {
    if (nonzero == 0) return true;
    if (chrono::steady_clock::now() > deadline) return false;
    int f = g + heuristic(nonzero);
    if (f > bound) return false;
    uint64_t key = hashGrid(grid);
    if (seen.count(key)) return false;
    seen.insert(key);
    vector<Move> moves;
    genMoves(grid, w, h, moves);
    struct Sc { int dec; int nd; Move m; };
    vector<Sc> cand;
    cand.reserve(moves.size());
    for (const auto& m : moves) {
        int sx, sy, dx, dy, os, od, nd; int nz = nonzero;
        if (!apply(m, grid, w, h, nz, sx, sy, dx, dy, os, od, nd)) continue;
        int dec = (os > 0 ? 1 : 0) + ((od > 0 && nd == 0) ? 1 : 0);
        undo(grid, w, sx, sy, dx, dy, nz, os, od, nd);
        cand.push_back({dec, nd, m});
    }
    sort(cand.begin(), cand.end(), [](const Sc& a, const Sc& b){ if (a.dec != b.dec) return a.dec > b.dec; return a.nd < b.nd; });
    for (const auto& c : cand) {
        int sx, sy, dx, dy, os, od, nd; int nz = nonzero;
        if (!apply(c.m, grid, w, h, nz, sx, sy, dx, dy, os, od, nd)) continue;
        path.push_back(c.m);
        if (idaDfs(grid, w, h, nz, g + 1, bound, path, seen, deadline)) return true;
        path.pop_back();
        undo(grid, w, sx, sy, dx, dy, nz, os, od, nd);
        if (chrono::steady_clock::now() > deadline) break;
    }
    seen.erase(key);
    return false;
}

static vector<Move> solveLevel(int w, int h, vector<int> grid, int timeMs) {
    int nonzero = 0;
    for (int v : grid) if (v != 0) nonzero++;
    vector<Move> path;
    auto deadline = chrono::steady_clock::now() + chrono::milliseconds(timeMs);
    int bound = heuristic(nonzero);
    auto idaDeadline = chrono::steady_clock::now() + chrono::milliseconds(timeMs / 6);
    while (chrono::steady_clock::now() < idaDeadline) {
        unordered_set<uint64_t> seen;
        if (idaDfs(grid, w, h, nonzero, 0, bound, path, seen, deadline)) return path;
        bound++;
    }
    auto sumGrid = [&](const vector<int>& g){ long long s=0; for (int v: g) s+=v; return s; };
    struct Node { vector<int> g; int nz; long long sum; vector<Move> p; };
    vector<Node> beam;
    beam.push_back({grid, nonzero, sumGrid(grid), {}});
    const int BEAM = 256;
    unordered_set<uint64_t> seen;
    seen.insert(hashGrid(grid));
    while (chrono::steady_clock::now() < deadline) {
        vector<Node> next;
        next.reserve(BEAM * 8);
        unordered_set<uint64_t> nextSeen;
        for (const auto& n : beam) {
            if (n.nz == 0) return n.p;
            vector<Move> moves;
            genMoves(n.g, w, h, moves);
            for (const auto& m : moves) {
                vector<int> g2 = n.g;
                int sx, sy, dx, dy, os, od, nd; int nz = n.nz;
                if (!apply(m, g2, w, h, nz, sx, sy, dx, dy, os, od, nd)) continue;
                uint64_t hsh = hashGrid(g2);
                if (seen.count(hsh) || nextSeen.count(hsh)) continue;
                nextSeen.insert(hsh);
                long long sum2 = n.sum - os - od + nd;
                vector<Move> p2 = n.p; p2.push_back(m);
                next.push_back({move(g2), nz, sum2, move(p2)});
            }
        }
        if (next.empty()) break;
        sort(next.begin(), next.end(), [&](const Node& a, const Node& b){ if (a.nz != b.nz) return a.nz < b.nz; return a.sum < b.sum; });
        if ((int)next.size() > BEAM) next.resize(BEAM);
        beam.swap(next);
        for (const auto& n : beam) seen.insert(hashGrid(n.g));
    }
    return {};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string levelCode = "qffmkiddphmqutkptjhwpnraapcrjodh";
    cout << levelCode << "\n";
    int w, h;
    if (!(cin >> w >> h)) return 0;
    vector<int> grid(w * h);
    for (int y = 0; y < h; y++) for (int x = 0; x < w; x++) cin >> grid[idx(x, y, w)];
    vector<Move> sol = solveLevel(w, h, grid, 9000);
    for (const auto& m : sol) cout << m.x << " " << m.y << " " << m.dir << " " << m.op << "\n";
    return 0;
}