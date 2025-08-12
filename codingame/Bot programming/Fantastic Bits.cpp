#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <unordered_set>
#include <limits>
using namespace std;

struct Vec {
    double x;
    double y;
};

static inline Vec operator+(const Vec& a, const Vec& b) { return {a.x + b.x, a.y + b.y}; }
static inline Vec operator-(const Vec& a, const Vec& b) { return {a.x - b.x, a.y - b.y}; }
static inline Vec operator*(const Vec& a, double k) { return {a.x * k, a.y * k}; }
static inline double dot(const Vec& a, const Vec& b) { return a.x * b.x + a.y * b.y; }
static inline double norm2(const Vec& a) { return a.x * a.x + a.y * a.y; }
static inline double norm(const Vec& a) { return sqrt(norm2(a)); }
static inline double distancePointToSegment(const Vec& p, const Vec& a, const Vec& b) {
    Vec ab{b.x - a.x, b.y - a.y};
    Vec ap{p.x - a.x, p.y - a.y};
    double ab2 = ab.x * ab.x + ab.y * ab.y;
    if (ab2 <= 1e-9) return norm(ap);
    double t = (ap.x * ab.x + ap.y * ab.y) / ab2;
    if (t < 0.0) t = 0.0; else if (t > 1.0) t = 1.0;
    Vec proj{a.x + ab.x * t, a.y + ab.y * t};
    Vec diff{p.x - proj.x, p.y - proj.y};
    return norm(diff);
}

struct Entity;
static inline int bestThrowY(const Vec& from, int goalX, const vector<Entity>& bludgers, const vector<Entity>& oppWizards);

static inline double leadMultiplier(const Vec& wizardPos, const Vec& snafflePos, const Vec& snaffleVel) {
    Vec toBall = snafflePos - wizardPos;
    double d = norm(toBall);
    double base = 0.6 + (d / 6000.0) * 0.6;
    if (base < 0.4) base = 0.4;
    if (base > 1.6) base = 1.6;
    double approaching = dot(snaffleVel, wizardPos - snafflePos);
    if (approaching > 0) base -= 0.2; else base += 0.2;
    if (base < 0.4) base = 0.4;
    if (base > 1.8) base = 1.8;
    return base;
}

struct Entity {
    int id;
    string type;
    Vec p;
    Vec v;
    int state;
};

static inline int clampi(int v, int lo, int hi) { return v < lo ? lo : (v > hi ? hi : v); }
static inline double clampd(double v, double lo, double hi) { return v < lo ? lo : (v > hi ? hi : v); }

static inline bool isAlignedToGoalForFlipendo(const Vec& wizardPos, const Vec& snafflePos, const Vec& goalPos, double cosThreshold) {
    Vec pushDir = snafflePos - wizardPos;
    Vec toGoal = goalPos - snafflePos;
    double nl = norm(pushDir);
    double nr = norm(toGoal);
    if (nl < 1e-6 || nr < 1e-6) return false;
    double c = dot(pushDir, toGoal) / (nl * nr);
    return c >= cosThreshold;
}

static inline int goalAimY(int currentY) {
    return 3750;
}

static inline int bestThrowY(const Vec& from, int goalX, const vector<Entity>& bludgers, const vector<Entity>& oppWizards) {
    static const int samples[] = {1750, 2250, 2750, 3250, 3750, 4250, 4750, 5250, 5750};
    double bestScore = -1e18;
    int bestY = 3750;
    Vec a{from.x, from.y};
    for (int y : samples) {
        Vec b{(double)goalX, (double)y};
        double minDist = 1e9;
        for (const auto& bl : bludgers) {
            double d = distancePointToSegment(bl.p, a, b);
            if (d < minDist) minDist = d;
        }
        double oppBlock = 0.0;
        for (const auto& ow : oppWizards) {
            double d = distancePointToSegment(ow.p, a, b);
            if (d < 800.0) oppBlock -= (800.0 - d) * 0.5;
        }
        double straightness = -fabs(from.y - y) * 0.001;
        double score = minDist + straightness + oppBlock;
        if (score > bestScore) { bestScore = score; bestY = y; }
    }
    return bestY;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int myTeamId;
    if (!(cin >> myTeamId)) return 0;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    const int myGoalX = myTeamId == 0 ? 0 : 16000;
    const int oppGoalX = myTeamId == 0 ? 16000 : 0;
    const int goalY = 3750;
    int turn = 0;
    vector<int> lastObliviateTurn(13, -100);

    while (true) {
        ++turn;
        int myScore, myMagic;
        if (!(cin >> myScore >> myMagic)) break;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        int oppScore, oppMagic;
        cin >> oppScore >> oppMagic;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        int entities;
        cin >> entities;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        vector<Entity> myWizards;
        vector<Entity> oppWizards;
        vector<Entity> snaffles;
        vector<Entity> bludgers;

        myWizards.reserve(2);
        oppWizards.reserve(2);
        snaffles.reserve(7);
        bludgers.reserve(2);

        for (int i = 0; i < entities; ++i) {
            int id, x, y, vx, vy, state;
            string t;
            cin >> id >> t >> x >> y >> vx >> vy >> state;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            Entity e{id, t, {(double)x, (double)y}, {(double)vx, (double)vy}, state};
            if (t == "WIZARD") myWizards.push_back(e);
            else if (t == "OPPONENT_WIZARD") oppWizards.push_back(e);
            else if (t == "SNAFFLE") snaffles.push_back(e);
            else if (t == "BLUDGER") bludgers.push_back(e);
        }

        sort(myWizards.begin(), myWizards.end(), [](const Entity& a, const Entity& b){ return a.id < b.id; });

        vector<string> actions(2, "");
        int magicLeft = myMagic;

        int availableCaster = -1;
        for (int wi = 0; wi < (int)myWizards.size(); ++wi) if (myWizards[wi].state == 0) { availableCaster = wi; break; }

        int oppCarrier = -1;
        double bestCarrierDanger = -1e18;
        for (int i = 0; i < (int)oppWizards.size(); ++i) {
            if (oppWizards[i].state != 1) continue;
            double xToMy = myTeamId == 0 ? oppWizards[i].p.x : (16000.0 - oppWizards[i].p.x);
            double score = 8000.0 - xToMy - 0.5 * fabs(oppWizards[i].p.y - goalY);
            if (score > bestCarrierDanger) { bestCarrierDanger = score; oppCarrier = i; }
        }

        if (oppCarrier != -1 && magicLeft >= 10 && availableCaster != -1 && actions[availableCaster].empty()) {
            actions[availableCaster] = string("PETRIFICUS ") + to_string(oppWizards[oppCarrier].id);
            magicLeft -= 10;
        }

        int threatIdx = -1;
        double bestThreatScore = -1e18;
        for (int i = 0; i < (int)snaffles.size(); ++i) {
            const auto& s = snaffles[i];
            bool towardsMyGoal = myTeamId == 0 ? (s.v.x < 0) : (s.v.x > 0);
            double xDistToMyLine = myTeamId == 0 ? s.p.x : (16000.0 - s.p.x);
            bool inVertical = s.p.y >= 1500 && s.p.y <= 6000;
            if (towardsMyGoal && inVertical) {
                double speedWeight = fabs(s.v.x) + 0.5 * fabs(s.v.y);
                double score = (6000.0 - xDistToMyLine) + 3.0 * speedWeight;
                if (xDistToMyLine <= 6000.0 && score > bestThreatScore) {
                    bestThreatScore = score;
                    threatIdx = i;
                }
            }
        }

        if (threatIdx != -1 && magicLeft >= 10) {
            int caster = availableCaster;
            if (caster == -1) {
                for (int wi = 0; wi < (int)myWizards.size(); ++wi) if (actions[wi].empty()) { caster = wi; break; }
            }
            if (caster != -1 && actions[caster].empty()) {
                actions[caster] = string("PETRIFICUS ") + to_string(snaffles[threatIdx].id);
                magicLeft -= 10;
            }
        }

        if (magicLeft >= 5 && !bludgers.empty()) {
            int caster = -1;
            for (int wi = 0; wi < (int)myWizards.size(); ++wi) {
                if (myWizards[wi].state == 0 && actions[wi].empty()) { caster = wi; break; }
            }
            if (caster != -1) {
                int targetBludger = -1;
                double bestRisk = 0.0;
                double bestMin = 1e18;
                for (const auto& b : bludgers) {
                    double minDist = 1e18;
                    Vec bestVec{0,0};
                    for (const auto& w : myWizards) {
                        Vec rel = w.p - b.p;
                        double d = norm(rel);
                        if (d < minDist) { minDist = d; bestVec = rel; }
                    }
                    double vlen = norm(b.v);
                    if (minDist < 3000.0 && vlen > 1e-6) {
                        Vec vdir{b.v.x / vlen, b.v.y / vlen};
                        double rlen = norm(bestVec);
                        if (rlen > 1e-6) {
                            Vec rdir{bestVec.x / rlen, bestVec.y / rlen};
                            double head = dot(vdir, rdir);
                            if (head > 0) {
                                double risk = head * (3000.0 - minDist) / 3000.0;
                                if (risk > bestRisk) { bestRisk = risk; targetBludger = b.id; bestMin = minDist; }
                            }
                        }
                    }
                }
                if (targetBludger != -1 && bestRisk >= 0.6 && bestMin <= 1800.0 && targetBludger >= 0 && targetBludger < (int)lastObliviateTurn.size() && (turn - lastObliviateTurn[targetBludger] >= 5)) {
                    actions[caster] = string("OBLIVIATE ") + to_string(targetBludger);
                    magicLeft -= 5;
                    lastObliviateTurn[targetBludger] = turn;
                }
            }
        }

        unordered_set<int> reservedSnaffles;
        if (threatIdx != -1) reservedSnaffles.insert(snaffles[threatIdx].id);

        int defenderIdx = -1;
        if (myWizards.size() == 2) {
            double d0 = myTeamId == 0 ? myWizards[0].p.x : (16000.0 - myWizards[0].p.x);
            double d1 = myTeamId == 0 ? myWizards[1].p.x : (16000.0 - myWizards[1].p.x);
            defenderIdx = d0 < d1 ? 0 : 1;
        }
        if (oppScore > myScore) defenderIdx = -1;

        bool hasIntercept = false;
        double interceptY = goalY;
        double interceptT = 1e18;
        for (int i = 0; i < (int)snaffles.size(); ++i) {
            const auto& s = snaffles[i];
            double vx = s.v.x;
            if (fabs(vx) < 1e-6) continue;
            bool towardsMyGoal = myTeamId == 0 ? (vx < 0) : (vx > 0);
            if (!towardsMyGoal) continue;
            double t = ((double)myGoalX - s.p.x) / vx;
            if (t <= 0) continue;
            double y = s.p.y + s.v.y * t;
            if (y < 1750.0 || y > 5750.0) continue;
            double score = 10000.0 / (1.0 + t);
            if (score > 1.0 && t < interceptT) {
                interceptT = t;
                interceptY = y;
                hasIntercept = true;
            }
        }

        for (int wi = 0; wi < (int)myWizards.size(); ++wi) {
            if (!actions[wi].empty()) continue;
            const auto& w = myWizards[wi];

            if (w.state == 1) {
                int ty = bestThrowY(w.p, oppGoalX, bludgers, oppWizards);
                int tx = oppGoalX;
                if (fabs(w.p.y - 3750.0) > 1200.0) ty = 3750;
                if ((myTeamId == 0 && w.p.x > 14000) || (myTeamId == 1 && w.p.x < 2000)) ty = clampi((int)w.p.y, 1750, 5750);
                actions[wi] = string("THROW ") + to_string(tx) + " " + to_string(ty) + " 500";
                continue;
            }

            if (oppCarrier != -1 && magicLeft >= 20 && actions[wi].empty()) {
                const auto& ow = oppWizards[oppCarrier];
                Vec dir = ow.p - w.p;
                double d = norm(dir);
                if (d > 1e-6 && d <= 6000.0) {
                    Vec toMyGoal{(double)myGoalX - ow.p.x, (double)goalY - ow.p.y};
                    double dd = dot(dir, toMyGoal);
                    if (dd < 0) {
                        actions[wi] = string("FLIPENDO ") + to_string(ow.id);
                        magicLeft -= 20;
                        continue;
                    }
                }
            }

            if (wi == defenderIdx && hasIntercept && actions[wi].empty()) {
                int guardX = myTeamId == 0 ? 2200 : 16000 - 2200;
                int iy = clampi((int)llround(interceptY), 1750, 5750);
                actions[wi] = string("MOVE ") + to_string(guardX) + " " + to_string(iy) + " 150";
                continue;
            }

            int flipIdx = -1;
            if (magicLeft >= 20) {
                double bestAlign = 0.0;
                for (int i = 0; i < (int)snaffles.size(); ++i) {
                    if (reservedSnaffles.count(snaffles[i].id)) continue;
                    const auto& s = snaffles[i];
                    Vec dir = s.p - w.p;
                    double dx = dir.x, dy = dir.y;
                    double d2 = dx * dx + dy * dy;
                    if (d2 > 9000.0 * 9000.0 || fabs(dx) < 1e-6) continue;
                    double t = ((double)oppGoalX - s.p.x) / dx;
                    if (t <= 0) continue;
                    double yhit = s.p.y + dy * t;
                    if (yhit < 1750.0 || yhit > 5750.0) continue;
                    Vec g1{(double)oppGoalX, 1750.0};
                    Vec g2{(double)oppGoalX, 5750.0};
                    Vec a = w.p;
                    Vec b = s.p;
                    double pathClear = 1.0;
                    for (const auto& bl : bludgers) {
                        double dseg = distancePointToSegment(bl.p, a, b);
                        if (dseg < 400.0) { pathClear = 0.7; break; }
                    }
                    Vec toG{(double)oppGoalX - s.p.x, (double)goalY - s.p.y};
                    double nl = sqrt(d2);
                    double nr = norm(toG);
                    if (nl < 1e-6 || nr < 1e-6) continue;
                    double c = (dx * toG.x + dy * toG.y) / (nl * nr);
                    double quality = c * pathClear;
                    if (quality > bestAlign && c >= 0.88) { bestAlign = quality; flipIdx = i; }
                }
            }

            if (flipIdx != -1 && magicLeft >= 20 && wi != defenderIdx) {
                actions[wi] = string("FLIPENDO ") + to_string(snaffles[flipIdx].id);
                magicLeft -= 20;
                reservedSnaffles.insert(snaffles[flipIdx].id);
                continue;
            }

            int accioIdx = -1;
            if (magicLeft >= 15) {
                double bestPullScore = -1e18;
                for (int i = 0; i < (int)snaffles.size(); ++i) {
                    if (reservedSnaffles.count(snaffles[i].id)) continue;
                    const auto& s = snaffles[i];
                    double dw = norm(s.p - w.p);
                    if (dw < 2800.0) continue;
                    if (myWizards.size() == 2) {
                        int other = wi ^ 1;
                        double dOther = norm(s.p - myWizards[other].p);
                        if (dOther < 2200.0) continue;
                    }
                    double toOppGoal = fabs((double)oppGoalX - s.p.x);
                    double toMyGoal = fabs((double)myGoalX - s.p.x);
                    double score = toMyGoal - 0.7 * toOppGoal + 0.001 * dw;
                    if (score > bestPullScore) {
                        bestPullScore = score;
                        accioIdx = i;
                    }
                }
            }

            if (accioIdx != -1 && magicLeft >= 15) {
                actions[wi] = string("ACCIO ") + to_string(snaffles[accioIdx].id);
                magicLeft -= 15;
                reservedSnaffles.insert(snaffles[accioIdx].id);
                continue;
            }

            int targetIdx = -1;
            double bestScore = -1e18;
            for (int i = 0; i < (int)snaffles.size(); ++i) {
                if (reservedSnaffles.count(snaffles[i].id)) continue;
                const auto& s = snaffles[i];
                double lead = leadMultiplier(w.p, s.p, s.v);
                Vec predict = s.p + s.v * lead;
                predict.x = clampd(predict.x, 0.0, 16000.0);
                predict.y = clampd(predict.y, 0.0, 7500.0);
                double d2 = norm2(predict - w.p);
                double toOpp = fabs((double)oppGoalX - predict.x);
                double toMy = fabs((double)myGoalX - predict.x);
                double centrality = -fabs(predict.y - 3750.0) * 0.05;
                double oppClosest = 0.0;
                if (!oppWizards.empty()) {
                    double minOpp = 1e18;
                    for (const auto& ow : oppWizards) {
                        double dd = norm(predict - ow.p);
                        if (dd < minOpp) minOpp = dd;
                    }
                    oppClosest = minOpp;
                }
                double sc = -d2 - 0.0008 * toOpp + 0.0001 * toMy + centrality + 0.1 * oppClosest;
                if (sc > bestScore) { bestScore = sc; targetIdx = i; }
            }

            if (targetIdx != -1) {
                reservedSnaffles.insert(snaffles[targetIdx].id);
                double leadGo = leadMultiplier(w.p, snaffles[targetIdx].p, snaffles[targetIdx].v) * 1.2;
                Vec predict = snaffles[targetIdx].p + snaffles[targetIdx].v * leadGo;
                int tx = clampi((int)llround(predict.x), 0, 16000);
                int ty = clampi((int)llround(predict.y), 0, 7500);
                actions[wi] = string("MOVE ") + to_string(tx) + " " + to_string(ty) + " 150";
            } else {
                if (wi == defenderIdx) {
                    int guardX = myTeamId == 0 ? 1800 : 16000 - 1800;
                    int gy = hasIntercept ? clampi((int)llround(interceptY), 1750, 5750) : goalY;
                    actions[wi] = string("MOVE ") + to_string(guardX) + " " + to_string(gy) + " 150";
                } else {
                    actions[wi] = string("MOVE 8000 3750 150");
                }
            }
        }

        for (int wi = 0; wi < 2; ++wi) {
            if (!actions[wi].empty()) {
                cout << actions[wi] << endl;
            } else {
                cout << "MOVE 8000 3750 150" << endl;
            }
        }
    }
    return 0;
}