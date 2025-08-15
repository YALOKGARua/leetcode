#include <bits/stdc++.h>
using namespace std;

struct Constraint {
    vector<int> g;
    int bulls;
    int cows;
    int presentMask;
    vector<int> suffixMask;
};

static inline int popcnt(int x) { return __builtin_popcount((unsigned)x); }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int L;
    if (!(cin >> L)) return 0;

    vector<int> baseDigits;
    for (int d = 1; d <= 9 && (int)baseDigits.size() < L; ++d) baseDigits.push_back(d);
    if ((int)baseDigits.size() < L) baseDigits.push_back(0);
    vector<int> lastGuess = baseDigits;

    static bool permuteMode = false;
    static vector<int> permGuess;
    static vector<int> permTestGuess;
    static int permLastBulls = -1;
    static bool permAwait = false;
    static int permI = 0, permJ = 1;

    auto toString = [&](const vector<int>& v) {
        string s; s.resize(L);
        for (int i = 0; i < L; ++i) s[i] = char('0' + v[i]);
        return s;
    };

    vector<Constraint> cons;

    while (true) {
        int bulls, cows;
        if (!(cin >> bulls >> cows)) break;
        if (bulls == -1 && cows == -1) {
            cout << toString(lastGuess) << endl;
            continue;
        }

        if (permuteMode) {
            if (permAwait) {
                if (bulls > permLastBulls) {
                    permGuess.swap(permTestGuess);
                    permLastBulls = bulls;
                }
                permAwait = false;
            }
            if (permLastBulls == L) {
                lastGuess = permGuess;
                cout << toString(lastGuess) << endl;
                continue;
            }
            bool issued = false;
            for (int i = permI; i < L && !issued; ++i) {
                for (int j = (i == permI ? permJ : i + 1); j < L; ++j) {
                    if (i == 0 && permGuess[j] == 0) continue;
                    permTestGuess = permGuess;
                    swap(permTestGuess[i], permTestGuess[j]);
                    lastGuess = permTestGuess;
                    cout << toString(lastGuess) << endl;
                    permAwait = true;
                    permI = i;
                    permJ = j + 1;
                    if (permJ >= L) { permI = i + 1; permJ = permI + 1; }
                    issued = true;
                    break;
                }
            }
            if (!issued) {
                permI = 0; permJ = 1;
                lastGuess = permGuess;
                cout << toString(lastGuess) << endl;
            }
            continue;
        }

        Constraint c;
        c.g = lastGuess;
        c.bulls = bulls;
        c.cows = cows;
        c.presentMask = 0;
        c.suffixMask.assign(L + 1, 0);
        for (int i = 0; i < L; ++i) c.presentMask |= 1 << c.g[i];
        for (int i = L - 1; i >= 0; --i) c.suffixMask[i] = c.suffixMask[i + 1] | (1 << c.g[i]);
        cons.push_back(std::move(c));

        if (!permuteMode && bulls + cows == L) {
            permuteMode = true;
            permGuess = lastGuess;
            permLastBulls = bulls;
            permAwait = false;
            permI = 0; permJ = 1;
            lastGuess = permGuess;
            cout << toString(lastGuess) << endl;
            continue;
        }

        int allowedMask = (1 << 10) - 1;
        int requiredMask = 0;
        for (const auto& cc : cons) {
            int mc = cc.bulls + cc.cows;
            if (mc == 0) allowedMask &= ~cc.presentMask;
            if (mc == L) { requiredMask |= cc.presentMask; allowedMask &= cc.presentMask; }
        }

        vector<array<int,10>> posCount(L);
        array<int,10> globalCount{}; globalCount.fill(0);
        for (const auto& cc : cons) {
            for (int i = 0; i < L; ++i) posCount[i][cc.g[i]]++;
            for (int d = 0; d < 10; ++d) if (cc.presentMask & (1 << d)) globalCount[d]++;
        }
        vector<vector<int>> order(L, vector<int>(10));
        for (int i = 0; i < L; ++i) {
            iota(order[i].begin(), order[i].end(), 0);
            sort(order[i].begin(), order[i].end(), [&](int a, int b){
                int ra = (requiredMask >> a) & 1;
                int rb = (requiredMask >> b) & 1;
                if (ra != rb) return ra > rb;
                if (posCount[i][a] != posCount[i][b]) return posCount[i][a] > posCount[i][b];
                if (globalCount[a] != globalCount[b]) return globalCount[a] > globalCount[b];
                return a < b;
            });
        }

        vector<int> posBan(L, 0);
        for (const auto& cc : cons) if (cc.bulls == 0) for (int i = 0; i < L; ++i) posBan[i] |= (1 << cc.g[i]);

        vector<array<unsigned char,10>> canPlace(L);
        for (int i = 0; i < L; ++i) {
            for (int d = 0; d < 10; ++d) {
                if (!(allowedMask & (1 << d))) { canPlace[i][d] = 0; continue; }
                if (posBan[i] & (1 << d)) { canPlace[i][d] = 0; continue; }
                if (i == 0 && d == 0) { canPlace[i][d] = 0; continue; }
                canPlace[i][d] = 1;
            }
        }

        auto evalBC = [&](const vector<int>& a, const vector<int>& b){
            int bulls = 0; int ma = 0, mb = 0;
            for (int i = 0; i < L; ++i) { if (a[i] == b[i]) ++bulls; ma |= 1 << a[i]; mb |= 1 << b[i]; }
            int m = __builtin_popcount((unsigned)(ma & mb));
            return pair<int,int>(bulls, m - bulls);
        };

        const int SAMPLE_LIMIT = 200;
        const int NODE_LIMIT = 30000;
        vector<vector<int>> samples;
        samples.reserve(SAMPLE_LIMIT);
        vector<int> result(L, -1);
        vector<unsigned char> assigned(L, 0);
        vector<int> bullsSo(cons.size(), 0);
        vector<int> matchesSo(cons.size(), 0);
        int nodes = 0;
        function<void(int,int)> dfsCollect = [&](int usedMask, int assignedCount){
            if ((int)samples.size() >= SAMPLE_LIMIT || nodes >= NODE_LIMIT) return;
            if (assignedCount == L) {
                for (size_t k = 0; k < cons.size(); ++k) {
                    if (bullsSo[k] != cons[k].bulls) return;
                    if (matchesSo[k] != cons[k].bulls + cons[k].cows) return;
                }
                samples.push_back(result);
                return;
            }
            ++nodes;
            int remain = L - assignedCount;
            int needReq = popcnt(requiredMask & ~usedMask);
            if (needReq > remain) return;
            int bestPos = -1;
            int bestChoices = 11;
            for (int i = 0; i < L; ++i) if (!assigned[i]) {
                int cnt = 0;
                for (int d : order[i]) {
                    if (!canPlace[i][d]) continue;
                    if (usedMask & (1 << d)) continue;
                    ++cnt;
                }
                if (cnt == 0) return;
                if (cnt < bestChoices) { bestChoices = cnt; bestPos = i; if (cnt == 1) break; }
            }
            int i = bestPos;
            for (int d : order[i]) {
                if (!canPlace[i][d]) continue;
                if (usedMask & (1 << d)) continue;
                int newUsed = usedMask | (1 << d);
                result[i] = d;
                assigned[i] = 1;
                bool ok = true;
                int remPos = L - (assignedCount + 1);
                for (size_t k = 0; k < cons.size(); ++k) {
                    int bNow = bullsSo[k] + (cons[k].g[i] == d);
                    if (bNow > cons[k].bulls) { ok = false; break; }
                    int pot = 0;
                    for (int j = 0; j < L; ++j) if (!assigned[j]) {
                        int dj = cons[k].g[j];
                        if (!(newUsed & (1 << dj)) && canPlace[j][dj]) ++pot;
                    }
                    if (bNow + pot < cons[k].bulls) { ok = false; break; }
                    int mNow = matchesSo[k] + ((cons[k].presentMask >> d) & 1);
                    if (mNow > cons[k].bulls + cons[k].cows) { ok = false; break; }
                    int maxMoreMatches = min(remPos, popcnt(cons[k].presentMask & ~newUsed));
                    if (mNow + maxMoreMatches < cons[k].bulls + cons[k].cows) { ok = false; break; }
                }
                if (ok) {
                    for (size_t k = 0; k < cons.size(); ++k) {
                        bullsSo[k] += (cons[k].g[i] == d);
                        matchesSo[k] += ((cons[k].presentMask >> d) & 1);
                    }
                    dfsCollect(newUsed, assignedCount + 1);
                    for (size_t k = 0; k < cons.size(); ++k) {
                        bullsSo[k] -= (cons[k].g[i] == d);
                        matchesSo[k] -= ((cons[k].presentMask >> d) & 1);
                    }
                }
                assigned[i] = 0;
                if ((int)samples.size() >= SAMPLE_LIMIT || nodes >= NODE_LIMIT) return;
            }
        };
        dfsCollect(0, 0);
        if (samples.empty()) samples.push_back(lastGuess);

        if ((int)samples.size() < 50) {
            int allowedList[10]; int allowedCnt = 0;
            for (int d = 0; d < 10; ++d) if (allowedMask & (1 << d)) allowedList[allowedCnt++] = d;
            auto makeProbe = [&](int seed){
                vector<int> g(L, -1);
                unsigned used = 0;
                for (int i = 0; i < L; ++i) {
                    for (int k = 0; k < allowedCnt; ++k) {
                        int idx = (k * 7 + i * 3 + seed * 11) % allowedCnt;
                        int d = allowedList[idx];
                        if ((used >> d) & 1) continue;
                        if (!canPlace[i][d]) continue;
                        if (i == 0 && d == 0) continue;
                        g[i] = d; used |= 1u << d; break;
                    }
                    if (g[i] == -1) return vector<int>();
                }
                return g;
            };
            int targetFill = min(50, SAMPLE_LIMIT);
            for (int s = 0; s < 80 && (int)samples.size() < targetFill; ++s) {
                auto g = makeProbe(s);
                if (g.empty()) continue;
                bool ok = true;
                for (const auto& cc : cons) {
                    int b = 0, m = 0, mask = 0;
                    for (int x : g) mask |= 1 << x;
                    for (int i = 0; i < L; ++i) if (g[i] == cc.g[i]) ++b;
                    m = popcnt(mask & cc.presentMask);
                    if (b != cc.bulls || (m - b) != cc.cows) { ok = false; break; }
                }
                if (!ok) continue;
                samples.push_back(std::move(g));
            }
        }
        int bestIdx = 0;
        int bestScore = INT_MAX;
        long long bestSS = LLONG_MAX;
        for (int i = 0; i < (int)samples.size(); ++i) {
            const auto& g = samples[i];
            int freq[128];
            memset(freq, 0, sizeof(freq));
            int worst = 0; long long ss = 0;
            for (int j = 0; j < (int)samples.size(); ++j) {
                auto bc = evalBC(g, samples[j]);
                int key = (bc.first << 3) | (bc.second & 7);
                int c = ++freq[key];
                if (c > worst) worst = c;
            }
            for (int k = 0; k < 128; ++k) if (freq[k]) { ss += 1LL * freq[k] * freq[k]; }
            if (worst < bestScore || (worst == bestScore && ss < bestSS)) { bestScore = worst; bestSS = ss; bestIdx = i; }
        }
        lastGuess = samples[bestIdx];
        cout << toString(lastGuess) << endl;
    }

    return 0;
}