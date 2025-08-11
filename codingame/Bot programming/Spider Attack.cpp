#include <bits/stdc++.h>
using namespace std;

struct Entity {
    int id;
    int type;
    int x;
    int y;
    int shieldLife;
    int isControlled;
    int health;
    int vx;
    int vy;
    int nearBase;
    int threatFor;
};

static long long sqr(long long v) { return v * v; }
static long long dist2(int x1, int y1, int x2, int y2) { return sqr((long long)x1 - x2) + sqr((long long)y1 - y2); }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int baseX, baseY;
    cin >> baseX >> baseY;
    int heroesPerPlayer;
    cin >> heroesPerPlayer;
    int turn = 0;

    const int mapW = 17630;
    const int mapH = 9000;
    const int windRange = 1280;
    
    const int controlRange = 2200;
    const int shieldRange = 2200;
    const int heroMove = 800;

    const int enemyBaseX = mapW - baseX;
    const int enemyBaseY = mapH - baseY;
    const bool topLeft = baseX < enemyBaseX;

    auto mirror = [&](int x, int y) -> pair<int,int> {
        if (topLeft) return {x, y};
        return {mapW - x, mapH - y};
    };

    pair<int,int> defP1 = mirror(3500, 1200);
    pair<int,int> defP2 = mirror(1200, 3500);
    pair<int,int> atkRally = mirror(15630, 4500);
    pair<int,int> atkRally2 = mirror(15000, 2000);
    pair<int,int> atkRally3 = mirror(16000, 7000);

    unordered_map<int,int> lastControlTurn;

    while (true) {
        int myHealth, myMana;
        int oppHealth, oppMana;
        cin >> myHealth >> myMana;
        cin >> oppHealth >> oppMana;

        int entityCount;
        cin >> entityCount;

        vector<Entity> monsters;
        vector<Entity> myHeroes;
        vector<Entity> oppHeroes;

        for (int i = 0; i < entityCount; i++) {
            Entity e;
            cin >> e.id >> e.type >> e.x >> e.y >> e.shieldLife >> e.isControlled >> e.health >> e.vx >> e.vy >> e.nearBase >> e.threatFor;
            if (e.type == 0) monsters.push_back(e);
            else if (e.type == 1) myHeroes.push_back(e);
            else oppHeroes.push_back(e);
        }

        sort(myHeroes.begin(), myHeroes.end(), [](const Entity &a, const Entity &b) { return a.id < b.id; });
        if (myHeroes.size() < 3) {
            cout << "WAIT\nWAIT\nWAIT\n";
            cout.flush();
            continue;
        }

        auto monstersThreatToUs = vector<int>();
        auto monstersNearUs = vector<int>();
        auto monstersNearEnemy = vector<int>();
        auto monstersNeutral = vector<int>();

        for (int i = 0; i < (int)monsters.size(); i++) {
            auto &m = monsters[i];
            long long dUs = dist2(m.x, m.y, baseX, baseY);
            long long dEnemy = dist2(m.x, m.y, enemyBaseX, enemyBaseY);
            if (m.threatFor == 1) monstersThreatToUs.push_back(i);
            if (dUs <= sqr(7000)) monstersNearUs.push_back(i);
            if (m.threatFor == 2 || dEnemy <= sqr(7000)) monstersNearEnemy.push_back(i);
            if (m.threatFor == 0) monstersNeutral.push_back(i);
        }
        
        const int offenseThreshold = 6;
        bool offenseMode = (int)monsters.size() >= offenseThreshold;


        auto nearestMonsterIdx = [&](const Entity &hero, const vector<int> &cand) -> int {
            int best = -1;
            long long bestD = (1LL<<62);
            for (int idx : cand) {
                long long d = dist2(hero.x, hero.y, monsters[idx].x, monsters[idx].y);
                if (d < bestD) { bestD = d; best = idx; }
            }
            return best;
        };

        auto monstersInRange = [&](const Entity &hero, int range) -> vector<int> {
            vector<int> res;
            long long r2 = sqr((long long)range);
            for (int i = 0; i < (int)monsters.size(); i++) {
                if (dist2(hero.x, hero.y, monsters[i].x, monsters[i].y) <= r2) res.push_back(i);
            }
            return res;
        };

        auto nearestToBaseIdx = [&](const vector<int> &cand, int bx, int by) -> int {
            int best = -1;
            long long bestD = (1LL<<62);
            for (int idx : cand) {
                long long d = dist2(monsters[idx].x, monsters[idx].y, bx, by);
                if (d < bestD) { bestD = d; best = idx; }
            }
            return best;
        };

        

        auto windSetupPoint = [&](const Entity &m, int bx, int by, int back) -> pair<int,int> {
            double dx = (double)bx - (double)m.x;
            double dy = (double)by - (double)m.y;
            double d = sqrt(dx*dx + dy*dy);
            if (d < 1e-6) return make_pair(m.x, m.y);
            double nx = dx / d;
            double ny = dy / d;
            int tx = (int)round((double)m.x - nx * (double)back);
            int ty = (int)round((double)m.y - ny * (double)back);
            tx = max(0, min(mapW, tx));
            ty = max(0, min(mapH, ty));
            return {tx, ty};
        };

        auto shouldWindDefense = [&](const Entity &hero) -> bool {
            if (myMana < 10) return false;
            auto inR = monstersInRange(hero, windRange);
            if (inR.empty()) return false;
            int countThreat = 0;
            long long minD = (1LL<<62);
            for (int idx : inR) {
                auto &m = monsters[idx];
                if (m.shieldLife > 0) continue;
                if (m.threatFor == 1) { countThreat++; continue; }
                long long db = dist2(m.x, m.y, baseX, baseY);
                if (db < minD) minD = db;
                if (db <= sqr(6500)) countThreat++;
            }
            if (countThreat >= 1) return true;
            if (minD <= sqr(3800)) return true;
            return false;
        };

        const int reserveManaForDefense = 20;
        auto shouldWindOffense = [&](const Entity &hero) -> bool {
            if (myMana < 10) return false;
            if ((int)monstersThreatToUs.size() > 0 && myMana <= reserveManaForDefense) return false;
            auto inR = monstersInRange(hero, windRange);
            if (inR.empty()) return false;
            double dx = (double)enemyBaseX - (double)hero.x;
            double dy = (double)enemyBaseY - (double)hero.y;
            double d = sqrt(dx*dx + dy*dy);
            if (d < 1e-6) return false;
            double ux = dx / d, uy = dy / d;
            int nonThreatCount = 0;
            bool lethal = false;
            int nearCount = 0;
            for (int idx : inR) {
                auto &m = monsters[idx];
                if (m.shieldLife > 0) continue;
                if (m.threatFor != 1) nonThreatCount++;
                double nx = (double)m.x + ux * 2200.0;
                double ny = (double)m.y + uy * 2200.0;
                double after = hypot(nx - (double)enemyBaseX, ny - (double)enemyBaseY);
                if (after <= 300.0) lethal = true;
                if (after <= 5000.0) nearCount++;
            }
            if (lethal) return true;
            if (nearCount >= 1 && myMana >= 20) return true;
            return nonThreatCount >= 2;
        };

        auto findControlTarget = [&](const Entity &hero) -> int {
            if (myMana < 10) return -1;
            long long r2 = sqr((long long)controlRange);
            int best = -1;
            long long bestDistToEnemy = (1LL<<62);
            for (int i = 0; i < (int)monsters.size(); i++) {
                auto &m = monsters[i];
                if (m.shieldLife > 0) continue;
                if (m.threatFor == 1) continue;
                if (dist2(hero.x, hero.y, m.x, m.y) > r2) continue;
                long long de = dist2(m.x, m.y, enemyBaseX, enemyBaseY);
                if (de > sqr(12000)) continue;
                if (de < bestDistToEnemy) { bestDistToEnemy = de; best = i; }
            }
            return best;
        };

        auto findDefControlTarget = [&](const Entity &hero) -> int {
            if (myMana < 10) return -1;
            long long r2 = sqr((long long)controlRange);
            int best = -1;
            long long closestToUs = (1LL<<62);
            for (int i = 0; i < (int)monsters.size(); i++) {
                auto &m = monsters[i];
                if (m.shieldLife > 0) continue;
                if (dist2(hero.x, hero.y, m.x, m.y) > r2) continue;
                if (m.threatFor != 1 && dist2(m.x, m.y, baseX, baseY) > sqr(7000)) continue;
                long long d = dist2(m.x, m.y, baseX, baseY);
                if (d < closestToUs) { closestToUs = d; best = i; }
            }
            return best;
        };

        auto findShieldTargetAtEnemyBase = [&](const Entity &hero) -> int {
            if (myMana < 10) return -1;
            long long r2 = sqr((long long)shieldRange);
            int best = -1;
            long long bestD = (1LL<<62);
            for (int i = 0; i < (int)monsters.size(); i++) {
                auto &m = monsters[i];
                if (m.shieldLife > 0) continue;
                if (dist2(hero.x, hero.y, m.x, m.y) > r2) continue;
                long long de = dist2(m.x, m.y, enemyBaseX, enemyBaseY);
                if (de > sqr(5000)) continue;
                if (de < bestD) { bestD = de; best = i; }
            }
            return best;
        };

        auto findOppHeroToControl = [&](const Entity &hero) -> int {
            if (myMana < 10) return -1;
            long long r2 = sqr((long long)controlRange);
            int bestIdx = -1;
            long long bestScore = -1;
            for (int i = 0; i < (int)oppHeroes.size(); i++) {
                auto &o = oppHeroes[i];
                if (o.shieldLife > 0) continue;
                if (dist2(hero.x, hero.y, o.x, o.y) > r2) continue;
                long long de = dist2(o.x, o.y, enemyBaseX, enemyBaseY);
                long long du = dist2(o.x, o.y, baseX, baseY);
                long long score = (de < sqr(7000) ? 1000000 : 0) + (sqr(8000) - min(de, (long long)sqr(8000))) + (sqr(10000) - min(du, (long long)sqr(10000)));
                if (score > bestScore) { bestScore = score; bestIdx = i; }
            }
            return bestIdx;
        };

        auto computeNextPos = [&](const Entity &hero, int tx, int ty) -> pair<int,int> {
            double dx = (double)tx - (double)hero.x;
            double dy = (double)ty - (double)hero.y;
            double d = sqrt(dx*dx + dy*dy);
            if (d <= (double)heroMove || d < 1e-6) {
                return {tx, ty};
            }
            double ux = dx / d, uy = dy / d;
            int nx = (int)round((double)hero.x + ux * (double)heroMove);
            int ny = (int)round((double)hero.y + uy * (double)heroMove);
            nx = max(0, min(mapW, nx));
            ny = max(0, min(mapH, ny));
            return {nx, ny};
        };

        auto minDistToAnyMonster = [&](int px, int py) -> double {
            double best = 1e18;
            for (auto &m : monsters) {
                double dx = (double)px - (double)m.x;
                double dy = (double)py - (double)m.y;
                double d = sqrt(dx*dx + dy*dy);
                if (d < best) best = d;
            }
            if (monsters.empty()) return 1e18;
            return best;
        };

        auto chooseSafeWindSetup = [&](const Entity &hero, const Entity &m, int bx, int by) -> pair<int,int> {
            vector<int> backs = {1100, 1200, 1300, 1400, 1000, 900};
            for (int b : backs) {
                auto pt = windSetupPoint(m, bx, by, b);
                auto np = computeNextPos(hero, pt.first, pt.second);
                double dTarget = sqrt((double)(np.first - m.x) * (np.first - m.x) + (double)(np.second - m.y) * (np.second - m.y));
                double dAny = minDistToAnyMonster(np.first, np.second);
                if (dTarget > 820.0 && dTarget < 1275.0 && dAny > 820.0) return pt;
            }
            return windSetupPoint(m, bx, by, 1200);
        };

        auto oppNear = [&](const Entity &hero, int range) -> bool {
            long long r2 = sqr((long long)range);
            for (auto &o : oppHeroes) if (dist2(hero.x, hero.y, o.x, o.y) <= r2) return true;
            return false;
        };

        auto shouldShield = [&](const Entity &hero) -> bool {
            if (hero.shieldLife > 0) return false;
            if (myMana < 20) return false;
            if (!oppNear(hero, shieldRange)) return false;
            if (!monstersThreatToUs.empty() && myMana < 40) return false;
            return true;
        };

        vector<string> out(3, "WAIT");

        Entity h0 = myHeroes[0];
        Entity h1 = myHeroes[1];
        Entity h2 = myHeroes[2];

        array<bool,3> isAtt = {offenseMode, offenseMode, offenseMode};

        if (!isAtt[0] && shouldWindDefense(h0)) {
            int tx0 = max(0, min(mapW, h0.x + (h0.x - baseX)));
            int ty0 = max(0, min(mapH, h0.y + (h0.y - baseY)));
            out[0] = string("SPELL WIND ") + to_string(tx0) + " " + to_string(ty0);
            myMana -= 10;
        } else if (!isAtt[0] && shouldShield(h0)) {
            out[0] = string("SPELL SHIELD ") + to_string(h0.id);
            myMana -= 10;
        } else if (isAtt[0] && myMana >= 10) {
            auto inR = monstersInRange(h0, windRange);
            for (int idx : inR) {
                if (monsters[idx].shieldLife > 0) continue;
                out[0] = string("SPELL WIND ") + to_string(enemyBaseX) + " " + to_string(enemyBaseY);
                myMana -= 10;
                break;
            }
        }
        if (!isAtt[1] && shouldWindDefense(h1)) {
            int tx1 = max(0, min(mapW, h1.x + (h1.x - baseX)));
            int ty1 = max(0, min(mapH, h1.y + (h1.y - baseY)));
            out[1] = string("SPELL WIND ") + to_string(tx1) + " " + to_string(ty1);
            myMana -= 10;
        } else if (!isAtt[1] && shouldShield(h1)) {
            out[1] = string("SPELL SHIELD ") + to_string(h1.id);
            myMana -= 10;
        } else if (isAtt[1] && myMana >= 10) {
            auto inR = monstersInRange(h1, windRange);
            for (int idx : inR) {
                if (monsters[idx].shieldLife > 0) continue;
                out[1] = string("SPELL WIND ") + to_string(enemyBaseX) + " " + to_string(enemyBaseY);
                myMana -= 10;
                break;
            }
        }

        if (out[0] == "WAIT") {
            int targetIdx = -1;
            if (!monstersThreatToUs.empty()) {
                targetIdx = nearestToBaseIdx(monstersThreatToUs, baseX, baseY);
            } else if (!monstersNearUs.empty()) {
                targetIdx = nearestMonsterIdx(h0, monstersNearUs);
            }
            if (!isAtt[0] && targetIdx != -1) {
                int tx = monsters[targetIdx].x + monsters[targetIdx].vx;
                int ty = monsters[targetIdx].y + monsters[targetIdx].vy;
                auto np = computeNextPos(h0, tx, ty);
                out[0] = string("MOVE ") + to_string(np.first) + " " + to_string(np.second);
            } else if (!isAtt[0]) {
                int gx = (baseX + enemyBaseX)/2;
                int gy = (baseY + enemyBaseY)/2;
                auto np = computeNextPos(h0, gx, gy);
                out[0] = string("MOVE ") + to_string(np.first) + " " + to_string(np.second);
            } else {
                int targetIdxA = -1;
                vector<int> cand;
                for (int i = 0; i < (int)monsters.size(); i++) {
                    if (monsters[i].threatFor == 1) continue;
                    if (dist2(monsters[i].x, monsters[i].y, enemyBaseX, enemyBaseY) <= sqr(10000)) cand.push_back(i);
                }
                if (!cand.empty()) targetIdxA = nearestToBaseIdx(cand, enemyBaseX, enemyBaseY);
                if (targetIdxA != -1) {
                    auto pt = chooseSafeWindSetup(h0, monsters[targetIdxA], enemyBaseX, enemyBaseY);
                    auto np = computeNextPos(h0, pt.first, pt.second);
                    if (minDistToAnyMonster(np.first, np.second) <= 820.0) {
                        int bx = (pt.first + enemyBaseX) / 2;
                        int by = (pt.second + enemyBaseY) / 2;
                        np = computeNextPos(h0, bx, by);
                    }
                    out[0] = string("MOVE ") + to_string(np.first) + " " + to_string(np.second);
                } else {
                    int phase = (turn / 16) % 3;
                    pair<int,int> patrol = phase == 0 ? atkRally2 : (phase == 1 ? atkRally : atkRally3);
                    out[0] = string("MOVE ") + to_string(patrol.first) + " " + to_string(patrol.second);
                }
            }
        }

        if (out[1] == "WAIT") {
            int targetIdx = -1;
            if (!monstersThreatToUs.empty()) {
                vector<int> cand = monstersThreatToUs;
                if (true) {
                    int used = nearestToBaseIdx(monstersThreatToUs, baseX, baseY);
                    if (used != -1) {
                        cand.erase(remove(cand.begin(), cand.end(), used), cand.end());
                    }
                }
                targetIdx = nearestToBaseIdx(cand.empty() ? monstersThreatToUs : cand, baseX, baseY);
            } else if (!monstersNearUs.empty()) {
                targetIdx = nearestMonsterIdx(h1, monstersNearUs);
            }
            if (!isAtt[1] && targetIdx != -1) {
                int tx = monsters[targetIdx].x + monsters[targetIdx].vx;
                int ty = monsters[targetIdx].y + monsters[targetIdx].vy;
                auto np = computeNextPos(h1, tx, ty);
                out[1] = string("MOVE ") + to_string(np.first) + " " + to_string(np.second);
            } else if (!isAtt[1]) {
                int gx = (baseX + enemyBaseX)/2;
                int gy = (baseY + enemyBaseY)/2;
                auto np = computeNextPos(h1, gx, gy);
                out[1] = string("MOVE ") + to_string(np.first) + " " + to_string(np.second);
            } else {
                int targetIdxA = -1;
                vector<int> cand;
                for (int i = 0; i < (int)monsters.size(); i++) {
                    if (monsters[i].threatFor == 1) continue;
                    if (dist2(monsters[i].x, monsters[i].y, enemyBaseX, enemyBaseY) <= sqr(10000)) cand.push_back(i);
                }
                if (!cand.empty()) targetIdxA = nearestToBaseIdx(cand, enemyBaseX, enemyBaseY);
                if (targetIdxA != -1) {
                    auto pt = chooseSafeWindSetup(h1, monsters[targetIdxA], enemyBaseX, enemyBaseY);
                    auto np = computeNextPos(h1, pt.first, pt.second);
                    if (minDistToAnyMonster(np.first, np.second) <= 820.0) {
                        int bx = (pt.first + enemyBaseX) / 2;
                        int by = (pt.second + enemyBaseY) / 2;
                        np = computeNextPos(h1, bx, by);
                    }
                    out[1] = string("MOVE ") + to_string(np.first) + " " + to_string(np.second);
                } else {
                    int phase = (turn / 16) % 3;
                    pair<int,int> patrol = phase == 0 ? atkRally : (phase == 1 ? atkRally3 : atkRally2);
                    out[1] = string("MOVE ") + to_string(patrol.first) + " " + to_string(patrol.second);
                }
            }
        }

        if (!isAtt[2]) {
            if (shouldWindDefense(h2)) {
                int tx2 = max(0, min(mapW, h2.x + (h2.x - baseX)));
                int ty2 = max(0, min(mapH, h2.y + (h2.y - baseY)));
                out[2] = string("SPELL WIND ") + to_string(tx2) + " " + to_string(ty2);
                myMana -= 10;
            } else if (shouldShield(h2)) {
                out[2] = string("SPELL SHIELD ") + to_string(h2.id);
                myMana -= 10;
            }
        } else {
            if (myMana >= 10) {
                auto inR2 = monstersInRange(h2, windRange);
                if (!inR2.empty()) {
                    bool casted = false;
                    for (int idx : inR2) {
                        if (monsters[idx].shieldLife > 0) continue;
                        out[2] = string("SPELL WIND ") + to_string(enemyBaseX) + " " + to_string(enemyBaseY);
                        myMana -= 10;
                        casted = true;
                        break;
                    }
                    if (!casted && shouldShield(h2) && myMana >= 30) {
                        out[2] = string("SPELL SHIELD ") + to_string(h2.id);
                        myMana -= 10;
                    }
                } else if (shouldShield(h2) && myMana >= 30) {
                    out[2] = string("SPELL SHIELD ") + to_string(h2.id);
                    myMana -= 10;
                } else if (shouldWindOffense(h2)) {
                    out[2] = string("SPELL WIND ") + to_string(enemyBaseX) + " " + to_string(enemyBaseY);
                    myMana -= 10;
                } else {
                    int shIdx = findShieldTargetAtEnemyBase(h2);
                    if (shIdx != -1) {
                        out[2] = string("SPELL SHIELD ") + to_string(monsters[shIdx].id);
                        myMana -= 10;
                    } else {
                        int ctrlIdx = -1;
                        if (myMana >= 30 || monstersThreatToUs.empty()) ctrlIdx = findControlTarget(h2);
                        if (ctrlIdx != -1) {
                            int mid = monsters[ctrlIdx].id;
                            if (!lastControlTurn.count(mid) || turn - lastControlTurn[mid] > 2) {
                                out[2] = string("SPELL CONTROL ") + to_string(mid) + " " + to_string(enemyBaseX) + " " + to_string(enemyBaseY);
                                myMana -= 10;
                                lastControlTurn[mid] = turn;
                            }
                        } else {
                            int oppIdx = findOppHeroToControl(h2);
                            if (oppIdx != -1) {
                                auto &o = oppHeroes[oppIdx];
                                out[2] = string("SPELL CONTROL ") + to_string(o.id) + " " + to_string(enemyBaseX) + " " + to_string(enemyBaseY);
                                myMana -= 10;
                            }
                        }
                    }
                }
            } else if (shouldWindOffense(h2)) {
                out[2] = string("SPELL WIND ") + to_string(enemyBaseX) + " " + to_string(enemyBaseY);
                myMana -= 10;
            }
        }

        if (out[0] == "WAIT") {
            int c = findDefControlTarget(h0);
            if (c != -1) { out[0] = string("SPELL CONTROL ") + to_string(monsters[c].id) + " " + to_string(enemyBaseX) + " " + to_string(enemyBaseY); myMana -= 10; }
        }
        if (out[1] == "WAIT") {
            int c = findDefControlTarget(h1);
            if (c != -1) { out[1] = string("SPELL CONTROL ") + to_string(monsters[c].id) + " " + to_string(enemyBaseX) + " " + to_string(enemyBaseY); myMana -= 10; }
        }

        if (out[2] == "WAIT") {
            if (!isAtt[2]) {
                int targetIdx = -1;
                if (!monstersThreatToUs.empty()) {
                    targetIdx = nearestToBaseIdx(monstersThreatToUs, baseX, baseY);
                } else if (!monstersNearUs.empty()) {
                    targetIdx = nearestMonsterIdx(h2, monstersNearUs);
                }
                if (targetIdx != -1) {
                    int tx = monsters[targetIdx].x + monsters[targetIdx].vx;
                    int ty = monsters[targetIdx].y + monsters[targetIdx].vy;
                    auto np = computeNextPos(h2, tx, ty);
                    out[2] = string("MOVE ") + to_string(np.first) + " " + to_string(np.second);
                } else {
                    int gx = (baseX + enemyBaseX)/2;
                    int gy = (baseY + enemyBaseY)/2;
                    auto np = computeNextPos(h2, gx, gy);
                    out[2] = string("MOVE ") + to_string(np.first) + " " + to_string(np.second);
                }
            } else {
                int targetIdx = -1;
                vector<int> cand;
                for (int i = 0; i < (int)monsters.size(); i++) {
                    if (monsters[i].threatFor == 1) continue;
                    cand.push_back(i);
                }
                if (!cand.empty()) targetIdx = nearestToBaseIdx(cand, enemyBaseX, enemyBaseY);
                if (targetIdx != -1) {
                    auto pt = chooseSafeWindSetup(h2, monsters[targetIdx], enemyBaseX, enemyBaseY);
                    out[2] = string("MOVE ") + to_string(pt.first) + " " + to_string(pt.second);
                } else {
                    int phase = (turn / 16) % 3;
                    pair<int,int> patrol = phase == 0 ? atkRally2 : (phase == 1 ? atkRally : atkRally3);
                    out[2] = string("MOVE ") + to_string(patrol.first) + " " + to_string(patrol.second);
                }
            }
        }

        cout << out[0] << "\n";
        cout << out[1] << "\n";
        cout << out[2] << "\n";
        cout.flush();
        turn++;
    }
    return 0;
}