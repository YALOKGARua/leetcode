#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <cctype>
#include <cstdint>
using namespace std;

static vector<int> knownBuildingOrder;
static unordered_set<int> knownBuildings;
static unordered_set<unsigned long long> existingEdges;
static bool podCreated = false;
static unordered_map<int, pair<int,int>> buildingPos;
static unordered_map<int, string> buildingKind;
static vector<int> padOrder;
static vector<int> moduleOrder;
static unordered_set<int> createdPods;
static unordered_map<int, int> moduleTypeOfBuilding;
static unordered_map<int, vector<int>> padTargets;
static unordered_map<int, vector<int>> modulesByType;
static unordered_map<unsigned long long, int> edgeCapacity;
static unordered_map<unsigned long long, int> podsAssignedOnEdge;
static int nextPodId = 1;
static unordered_set<int> usedPodIds;

static inline vector<int> extractIntegers(const string& s) {
    vector<int> out;
    long long value = 0;
    bool inNumber = false;
    bool negative = false;
    for (char ch : s) {
        if (!inNumber) {
            if (ch == '-') {
                inNumber = true;
                negative = true;
                value = 0;
            } else if (ch >= '0' && ch <= '9') {
                inNumber = true;
                negative = false;
                value = ch - '0';
            }
        } else {
            if (ch >= '0' && ch <= '9') {
                value = value * 10 + (ch - '0');
            } else {
                out.push_back(negative ? static_cast<int>(-value) : static_cast<int>(value));
                inNumber = false;
                negative = false;
                value = 0;
            }
        }
    }
    if (inNumber) out.push_back(negative ? static_cast<int>(-value) : static_cast<int>(value));
    return out;
}

static inline unsigned long long edgeKey(int a, int b) {
    int x = min(a, b);
    int y = max(a, b);
    return (static_cast<unsigned long long>(static_cast<uint32_t>(x)) << 32) |
           static_cast<unsigned long long>(static_cast<uint32_t>(y));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        int resources;
        if (!(cin >> resources)) return 0;
        cin.ignore();
        cerr << "R " << resources << '\n';
        podsAssignedOnEdge.clear();

        int num_travel_routes;
        cin >> num_travel_routes;
        cin.ignore();
        cerr << "TRN " << num_travel_routes << '\n';
        vector<pair<int,int>> routeEdges;
        for (int i = 0; i < num_travel_routes; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            cin.ignore();
            cerr << "TR " << a << ' ' << b << ' ' << c << '\n';
            if (!knownBuildings.count(a)) { knownBuildings.insert(a); knownBuildingOrder.push_back(a); }
            if (!knownBuildings.count(b)) { knownBuildings.insert(b); knownBuildingOrder.push_back(b); }
            existingEdges.insert(edgeKey(a, b));
            routeEdges.emplace_back(a, b);
            edgeCapacity[edgeKey(a, b)] = c;
            (void)c;
        }

        int num_pods;
        cin >> num_pods;
        cin.ignore();
        cerr << "PN " << num_pods << '\n';
        usedPodIds.clear();
        int maxSeenPodId = 0;
        for (int i = 0; i < num_pods; i++) {
            string line;
            getline(cin, line);
            cerr << "PO " << line << '\n';
            vector<int> ints = extractIntegers(line);
            if (!ints.empty()) { maxSeenPodId = max(maxSeenPodId, ints[0]); usedPodIds.insert(ints[0]); createdPods.insert(ints[0]); }
            if (ints.size() >= 4) {
                int a = ints[2];
                int b = ints[3];
                podsAssignedOnEdge[edgeKey(a, b)]++;
            }
        }
        if (maxSeenPodId >= nextPodId) nextPodId = maxSeenPodId + 1;

        int num_new_buildings;
        cin >> num_new_buildings;
        cin.ignore();
        cerr << "BN " << num_new_buildings << '\n';
        vector<int> newPads;
        vector<int> newModules;
        for (int i = 0; i < num_new_buildings; i++) {
            string line;
            getline(cin, line);
            cerr << "B " << line << '\n';
            vector<int> ints = extractIntegers(line);
            if (!ints.empty()) {
                int id = ints[0];
                if (ints.size() >= 4) {
                    int t = ints[0];
                    int bid = ints[1];
                    int x = ints[2];
                    int y = ints[3];
                    if (!knownBuildings.count(bid)) {
                        knownBuildings.insert(bid);
                        knownBuildingOrder.push_back(bid);
                    }
                    buildingPos[bid] = {x, y};
                    if (t == 0 && ints.size() >= 5) {
                        int cnt = ints[4];
                        vector<int> targets;
                        for (int k = 0; k < cnt && 5 + k < (int)ints.size(); k++) targets.push_back(ints[5 + k]);
                        padTargets[bid] = targets;
                        buildingKind[bid] = "PAD";
                        padOrder.push_back(bid);
                        newPads.push_back(bid);
                    } else {
                        moduleTypeOfBuilding[bid] = t;
                        modulesByType[t].push_back(bid);
                        buildingKind[bid] = "MODULE";
                        moduleOrder.push_back(bid);
                        newModules.push_back(bid);
                    }
                }
            }
        }

        vector<string> actions;
        int actionBudget = 40;
        const int maxTotalPods = 480;
        int availablePodRoom = max(0, maxTotalPods - (int)usedPodIds.size());

        auto addTube = [&](int u, int v) {
            if (!existingEdges.count(edgeKey(u, v))) {
                if (actionBudget <= 0) return;
                actions.push_back(string("TUBE ") + to_string(u) + " " + to_string(v));
                existingEdges.insert(edgeKey(u, v));
                edgeCapacity[edgeKey(u, v)] = max(1, edgeCapacity[edgeKey(u, v)]);
                actionBudget--;
            }
        };

        auto allocatePodId = [&]() -> int {
            for (int id = 0; id <= 500; id++) {
                if (!usedPodIds.count(id)) { usedPodIds.insert(id); return id; }
            }
            return -1;
        };

        auto addPodRoute = [&](int a, int b) {
            if (actionBudget <= 0 || availablePodRoom <= 0) return;
            int podId = allocatePodId();
            if (podId < 0) return;
            string pod = string("POD ") + to_string(podId);
            for (int i = 0; i < 20; i++) {
                pod += " ";
                pod += to_string(a);
                pod += " ";
                pod += to_string(b);
            }
            actions.push_back(pod);
            createdPods.insert(podId);
            podCreated = true;
            podsAssignedOnEdge[edgeKey(a, b)]++;
            actionBudget--;
            availablePodRoom--;
        };

        auto addUpgrade = [&](int u, int v) {
            if (actionBudget <= 0) return;
            actions.push_back(string("UPGRADE ") + to_string(u) + " " + to_string(v));
            edgeCapacity[edgeKey(u, v)]++;
            actionBudget--;
        };

        auto addPodRouteRoundRobin = [&](int padId, const vector<int>& mods) {
            if (mods.empty() || actionBudget <= 0 || availablePodRoom <= 0) return;
            int podId = allocatePodId();
            if (podId < 0) return;
            string pod = string("POD ") + to_string(podId);
            for (int i = 0; i < 20; i++) {
                int m = mods[i % mods.size()];
                pod += " ";
                pod += to_string(padId);
                pod += " ";
                pod += to_string(m);
                podsAssignedOnEdge[edgeKey(padId, m)]++;
            }
            actions.push_back(pod);
            createdPods.insert(podId);
            podCreated = true;
            actionBudget--;
            availablePodRoom--;
        };

        auto chooseNearestModule = [&](int padId, int targetType) -> int {
            auto it = modulesByType.find(targetType);
            if (it == modulesByType.end() || it->second.empty()) return -1;
            pair<int,int> pp = buildingPos.count(padId) ? buildingPos[padId] : make_pair(0,0);
            long long bestD = (1LL<<62);
            int best = -1;
            for (int mid : it->second) {
                pair<int,int> mp = buildingPos.count(mid) ? buildingPos[mid] : make_pair(0,0);
                long long dx = pp.first - mp.first;
                long long dy = pp.second - mp.second;
                long long d2 = dx*dx + dy*dy;
                if (d2 < bestD) { bestD = d2; best = mid; }
            }
            return best;
        };

        for (int padId : newPads) {
            vector<int> targets = padTargets[padId];
            int bestType = -1;
            if (!targets.empty()) {
                unordered_map<int,int> freq;
                for (int t : targets) freq[t]++;
                int mx = -1;
                for (auto& kv : freq) {
                    if (kv.second > mx) { mx = kv.second; bestType = kv.first; }
                }
            }
            if (bestType == -1 && !moduleOrder.empty()) bestType = moduleTypeOfBuilding[moduleOrder[0]];
            if (bestType != -1) {
                vector<int> mods = modulesByType[bestType];
                pair<int,int> pp = buildingPos[padId];
                sort(mods.begin(), mods.end(), [&](int m1, int m2){
                    pair<int,int> p1 = buildingPos[m1];
                    pair<int,int> p2 = buildingPos[m2];
                    long long d1 = 1LL*(pp.first - p1.first)*(pp.first - p1.first) + 1LL*(pp.second - p1.second)*(pp.second - p1.second);
                    long long d2 = 1LL*(pp.first - p2.first)*(pp.first - p2.first) + 1LL*(pp.second - p2.second)*(pp.second - p2.second);
                    return d1 < d2;
                });
                int take = min(3, (int)mods.size());
                for (int i = 0; i < take; i++) {
                    int modId = mods[i];
                    addTube(padId, modId);
                    int desiredCap = 3;
                    while (edgeCapacity[edgeKey(padId, modId)] < desiredCap && actionBudget > 0) addUpgrade(padId, modId);
                    int demand = (int)targets.size();
                    int desiredPods = min(3, max(1, demand / max(1, take*20)) + 1);
                    int existingPods = podsAssignedOnEdge[edgeKey(padId, modId)];
                    while (existingPods < desiredPods && actionBudget > 0 && availablePodRoom > 0) { addPodRoute(padId, modId); existingPods++; }
                    if (actionBudget <= 0) break;
                }
            }
        }

        for (int padId : padOrder) {
            vector<int> targets = padTargets[padId];
            if (targets.empty()) continue;
            unordered_map<int,int> freq;
            for (int t : targets) freq[t]++;
            vector<pair<int,int>> types;
            types.reserve(freq.size());
            for (auto& kv : freq) types.push_back({kv.second, kv.first});
            sort(types.rbegin(), types.rend());
            int consider = min(2, (int)types.size());
            for (int ti = 0; ti < consider && actionBudget > 0; ti++) {
                int t = types[ti].second;
                vector<int> mods = modulesByType[t];
                if (mods.empty()) continue;
                pair<int,int> pp = buildingPos[padId];
                sort(mods.begin(), mods.end(), [&](int m1, int m2){
                    pair<int,int> p1 = buildingPos[m1];
                    pair<int,int> p2 = buildingPos[m2];
                    long long d1 = 1LL*(pp.first - p1.first)*(pp.first - p1.first) + 1LL*(pp.second - p1.second)*(pp.second - p1.second);
                    long long d2 = 1LL*(pp.first - p2.first)*(pp.first - p2.first) + 1LL*(pp.second - p2.second)*(pp.second - p2.second);
                    return d1 < d2;
                });
                int take = min(3, (int)mods.size());
                for (int i = 0; i < take && actionBudget > 0; i++) {
                    int modId = mods[i];
                    addTube(padId, modId);
                    int desiredCap = 3;
                    while (edgeCapacity[edgeKey(padId, modId)] < desiredCap && actionBudget > 0) addUpgrade(padId, modId);
                    int demandT = types[ti].first;
                    vector<int> chosenMods;
                    for (int j = 0; j < take; j++) chosenMods.push_back(mods[j]);
                    int podsNeeded = min(2, max(1, demandT / max(1, take*15)));
                    for (int p = 0; p < podsNeeded && actionBudget > 0 && availablePodRoom > 0; p++) addPodRouteRoundRobin(padId, chosenMods);
                }
            }
        }

        for (auto& e : routeEdges) {
            int u = e.first, v = e.second;
            string ku = buildingKind.count(u) ? buildingKind[u] : string();
            string kv = buildingKind.count(v) ? buildingKind[v] : string();
            int pad = -1, mod = -1;
            if (ku == "PAD" && kv == "MODULE") { pad = u; mod = v; }
            else if (kv == "PAD" && ku == "MODULE") { pad = v; mod = u; }
            if (pad == -1) continue;
            int cap = edgeCapacity[edgeKey(u, v)];
            int desired = min(2, max(1, cap));
            if (cap < desired) {
                addUpgrade(u, v);
                cap = edgeCapacity[edgeKey(u, v)];
            }
            int have = podsAssignedOnEdge[edgeKey(u, v)];
            while (have < desired && actionBudget > 0 && availablePodRoom > 0) { addPodRoute(pad, mod); have++; }
            if (actionBudget <= 0) break;
        }

        if (actions.empty()) cout << "WAIT" << endl;
        else {
            string out;
            for (size_t i = 0; i < actions.size(); i++) {
                if (i) out += ";";
                out += actions[i];
            }
            cerr << "A " << out << '\n';
            cout << out << endl;
        }
    }
}