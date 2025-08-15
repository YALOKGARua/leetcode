    #include <iostream>
    #include <vector>
    #include <string>
    #include <algorithm>
    #include <numeric>
    #include <cmath>
    #include <unordered_map>
    #include <climits>
    using namespace std;

    enum class EntityType { Wizard, OpponentWizard, Snaffle, Bludger };

    struct Entity {
        int id;
        EntityType type;
        int x;
        int y;
        int vx;
        int vy;
        int state;
    };

    static inline long long dist2(int ax, int ay, int bx, int by) {
        long long dx = ax - bx;
        long long dy = ay - by;
        return dx * dx + dy * dy;
    }

    static inline double dist(int ax, int ay, int bx, int by) {
        return sqrt((double)dist2(ax, ay, bx, by));
    }

    static inline int clampi(int v, int lo, int hi) { return v < lo ? lo : (v > hi ? hi : v); }

    int main() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);

        int myTeamId;
        cin >> myTeamId; cin.ignore();

        const int myGoalX = myTeamId == 0 ? 0 : 16000;
        const int oppGoalX = myTeamId == 0 ? 16000 : 0;
        const int goalY = 3750;
        int turn = 0;
        unordered_map<int,int> petrBlock;
        unordered_map<int,int> oblvBlock;
        unordered_map<int,int> accioBlock;
        unordered_map<int,int> flipBlock;

        while (true) {
            int myScore, myMagic;
            cin >> myScore >> myMagic; cin.ignore();
            int oppScore, oppMagic;
            cin >> oppScore >> oppMagic; cin.ignore();
            int entitiesCount;
            cin >> entitiesCount; cin.ignore();

            vector<Entity> myWizards;
            vector<Entity> oppWizards;
            vector<Entity> snaffles;
            vector<Entity> bludgers;

            myWizards.reserve(2);
            oppWizards.reserve(2);
            snaffles.reserve(8);
            bludgers.reserve(2);

            for (int i = 0; i < entitiesCount; i++) {
                int id, x, y, vx, vy, state;
                string type;
                cin >> id >> type >> x >> y >> vx >> vy >> state; cin.ignore();
                Entity e{ id, EntityType::Snaffle, x, y, vx, vy, state };
                if (type == "WIZARD") e.type = EntityType::Wizard;
                else if (type == "OPPONENT_WIZARD") e.type = EntityType::OpponentWizard;
                else if (type == "SNAFFLE") e.type = EntityType::Snaffle;
                else e.type = EntityType::Bludger;
                if (e.type == EntityType::Wizard) myWizards.push_back(e);
                else if (e.type == EntityType::OpponentWizard) oppWizards.push_back(e);
                else if (e.type == EntityType::Snaffle) snaffles.push_back(e);
                else bludgers.push_back(e);
            }

            sort(myWizards.begin(), myWizards.end(), [](const Entity& a, const Entity& b){ return a.id < b.id; });

            auto aimYForThrow = [&](const Entity& w) {
                vector<int> cands = {
                    goalY,
                    clampi(goalY + 1200, 1000, 6500),
                    clampi(goalY - 1200, 1000, 6500),
                    clampi(goalY + 2000, 1000, 6500),
                    clampi(goalY - 2000, 1000, 6500)
                };
                int bestY = cands[0];
                long long bestScore = LLONG_MIN;
                for (int cy : cands) {
                    long long minOppDY = (1LL<<62);
                    for (const auto& ow : oppWizards) {
                        long long dy = llabs((long long)ow.y - (long long)cy);
                        if (dy < minOppDY) minOppDY = dy;
                    }
                    long long aimEase = -llabs((long long)w.y - (long long)cy);
                    long long score = minOppDY * 10 + aimEase;
                    if (score > bestScore) { bestScore = score; bestY = cy; }
                }
                return bestY;
            };

            int availableMagic = myMagic;

            int dangerIdx = -1;
            long long dangerScore = (1LL<<62);
            for (int i = 0; i < (int)snaffles.size(); i++) {
                const auto& s = snaffles[i];
                bool towardUs = myTeamId == 0 ? (s.vx < 0) : (s.vx > 0);
                long long dxGoal = llabs((long long)s.x - (long long)myGoalX);
                long long score = dxGoal + (towardUs ? 0 : 8000);
                if (score < dangerScore) { dangerScore = score; dangerIdx = i; }
            }
            int goalieIndex = -1;
            if (dangerIdx != -1 && !myWizards.empty()) {
                long long bestD = (1LL<<62);
                for (int i = 0; i < (int)myWizards.size(); i++) {
                    long long d2 = dist2(myWizards[i].x, myWizards[i].y, snaffles[dangerIdx].x, snaffles[dangerIdx].y);
                    if (d2 < bestD) { bestD = d2; goalieIndex = i; }
                }
                const auto& ds = snaffles[dangerIdx];
                bool towardUs = myTeamId == 0 ? (ds.vx < 0) : (ds.vx > 0);
                long long dxGoal = llabs((long long)ds.x - (long long)myGoalX);
                if (!towardUs || dxGoal > 8000) goalieIndex = -1;
            }

            vector<int> assignedSnaffleForWizard(2, -1);
            if (!snaffles.empty()) {
                vector<long long> oppMinD2(snaffles.size(), (1LL<<62));
                for (int si = 0; si < (int)snaffles.size(); si++) {
                    for (const auto& ow : oppWizards) {
                        long long d2 = dist2(ow.x, ow.y, snaffles[si].x, snaffles[si].y);
                        if (d2 < oppMinD2[si]) oppMinD2[si] = d2;
                    }
                }
                vector<int> order(myWizards.size());
                iota(order.begin(), order.end(), 0);
                vector<bool> used(snaffles.size(), false);
                for (int k = 0; k < (int)order.size(); k++) {
                    int wi = order[k];
                    int best = -1;
                    long long bestCost = (1LL<<62);
                    for (int si = 0; si < (int)snaffles.size(); si++) {
                        if (used[si]) continue;
                        const auto& s = snaffles[si];
                        long long myD2 = dist2(myWizards[wi].x, myWizards[wi].y, s.x, s.y);
                        long long goalD2 = dist2(s.x, s.y, oppGoalX, goalY);
                        long long oppD2 = oppMinD2[si];
                        long long cost = myD2 - oppD2/2 + goalD2/4 + (s.state ? 200000000LL : 0LL);
                        if (cost < bestCost) { bestCost = cost; best = si; }
                    }
                    if (best != -1) { assignedSnaffleForWizard[wi] = best; used[best] = true; }
                }
            }

            vector<string> outputs;
            outputs.reserve(2);

            for (int wi = 0; wi < (int)myWizards.size(); wi++) {
                const Entity& w = myWizards[wi];
                if (w.state == 1) {
                    int ty = aimYForThrow(w);
                    outputs.push_back(string("THROW ") + to_string(oppGoalX) + " " + to_string(ty) + " 500");
                    continue;
                }

                if (goalieIndex == wi && dangerIdx != -1) {
                    const Entity& ds = snaffles[dangerIdx];
                    bool towardUs = myTeamId == 0 ? (ds.vx < 0) : (ds.vx > 0);
                    long long dGoalX = llabs((long long)ds.x - (long long)myGoalX);
                    if (availableMagic >= 10 && towardUs && dGoalX < 3500 && (!petrBlock.count(ds.id) || turn >= petrBlock[ds.id])) {
                        outputs.push_back(string("PETRIFICUS ") + to_string(ds.id));
                        availableMagic -= 10;
                        petrBlock[ds.id] = turn + 2;
                        continue;
                    }
                    bool ahead = myTeamId == 0 ? (ds.x < w.x) : (ds.x > w.x);
                    long long d2wd = dist2(w.x, w.y, ds.x, ds.y);
                    if (availableMagic >= 15 && towardUs && !ahead && d2wd > 2000LL*2000LL && (!accioBlock.count(ds.id) || turn >= accioBlock[ds.id])) {
                        outputs.push_back(string("ACCIO ") + to_string(ds.id));
                        availableMagic -= 15;
                        accioBlock[ds.id] = turn + 4;
                        continue;
                    }
                    int ix = myTeamId == 0 ? 1800 : 14200;
                    int iy = clampi(ds.y + ds.vy * 2, 1000, 6500);
                    outputs.push_back(string("MOVE ") + to_string(ix) + " " + to_string(iy) + " 150");
                    continue;
                }

                int targetIdx = assignedSnaffleForWizard[wi];
                if (!bludgers.empty() && availableMagic >= 5) {
                    int nbIdx = -1; long long nbBest = (1LL<<62);
                    for (int bi = 0; bi < (int)bludgers.size(); bi++) {
                        long long d2b = dist2(w.x, w.y, bludgers[bi].x, bludgers[bi].y);
                        if (d2b < nbBest) { nbBest = d2b; nbIdx = bi; }
                    }
                    if (nbIdx != -1 && nbBest < 2000LL*2000LL) {
                        int bid = bludgers[nbIdx].id;
                        if (!oblvBlock.count(bid) || turn >= oblvBlock[bid]) {
                            outputs.push_back(string("OBLIVIATE ") + to_string(bid));
                            availableMagic -= 5;
                            oblvBlock[bid] = turn + 5;
                            continue;
                        }
                    }
                }
                if (targetIdx != -1) {
                    const Entity& s = snaffles[targetIdx];
                    long long myD2now = dist2(w.x, w.y, s.x, s.y);
                    long long oppD2min = (1LL<<62);
                    for (const auto& ow : oppWizards) oppD2min = min(oppD2min, dist2(ow.x, ow.y, s.x, s.y));
                    if (oppD2min + 3000000LL < myD2now) {
                        int alt = -1; long long bestAlt = (1LL<<62);
                        for (int si = 0; si < (int)snaffles.size(); si++) {
                            if (si == targetIdx) continue;
                            long long d2a = dist2(w.x, w.y, snaffles[si].x, snaffles[si].y);
                            long long o2a = (1LL<<62);
                            for (const auto& ow : oppWizards) o2a = min(o2a, dist2(ow.x, ow.y, snaffles[si].x, snaffles[si].y));
                            long long cost = d2a - o2a/2;
                            if (cost < bestAlt) { bestAlt = cost; alt = si; }
                        }
                        if (alt != -1) targetIdx = alt;
                    }
                    bool canFlipendo = false;
                    if (availableMagic >= 20) {
                        int gx = oppGoalX;
                        int gy = goalY;
                        double wx = (double)w.x, wy = (double)w.y;
                        double sx = (double)s.x, sy = (double)s.y;
                        double vx1 = sx - wx, vy1 = sy - wy;
                        double vx2 = (double)gx - wx, vy2 = (double)gy - wy;
                        double n1 = sqrt(vx1*vx1 + vy1*vy1);
                        double n2 = sqrt(vx2*vx2 + vy2*vy2);
                        if (n1 > 1e-6 && n2 > 1e-6) {
                            double cosang = (vx1*vx2 + vy1*vy2) / (n1 * n2);
                            bool inFront = myTeamId == 0 ? (w.x <= s.x) : (w.x >= s.x);
                            if (cosang > 0.96 && inFront && n1 <= 5500.0) canFlipendo = true;
                        }
                    }
                    if (canFlipendo && (!flipBlock.count(s.id) || turn >= flipBlock[s.id])) {
                        outputs.push_back(string("FLIPENDO ") + to_string(s.id));
                        availableMagic -= 20;
                        flipBlock[s.id] = turn + 3;
                    } else {
                        bool canAccio = false;
                        if (availableMagic >= 15 && (!accioBlock.count(s.id) || turn >= accioBlock[s.id])) {
                            bool safeZone = myTeamId == 0 ? (w.x > 2800) : (w.x < 13200);
                            bool ahead = myTeamId == 0 ? (s.x > w.x) : (s.x < w.x);
                            long long d2 = dist2(w.x, w.y, s.x, s.y);
                            if (safeZone && ahead && d2 > 2500LL*2500LL) canAccio = true;
                        }
                        if (canAccio) {
                            outputs.push_back(string("ACCIO ") + to_string(s.id));
                            availableMagic -= 15;
                            accioBlock[s.id] = turn + 4;
                        } else {
                            int tx = clampi(s.x + s.vx * 2, 1, 15999);
                            int ty = clampi(s.y + s.vy * 2, 1, 7499);
                            outputs.push_back(string("MOVE ") + to_string(tx) + " " + to_string(ty) + " 150");
                        }
                    }
                } else {
                    int roamX = myTeamId == 0 ? 7000 : 9000;
                    int roamY = goalY;
                    outputs.push_back(string("MOVE ") + to_string(roamX) + " " + to_string(roamY) + " 150");
                }
            }

            while ((int)outputs.size() < 2) outputs.push_back("MOVE 8000 3750 150");
            cout << outputs[0] << '\n' << outputs[1] << '\n' << flush;
            turn++;
        }
    }


