#include <iostream>
#include <vector>
#include <utility>
#include <climits>
#include <cmath>
using namespace std;
static constexpr bool kDebug = false;

static const int GRID_WIDTH = 96;
static const int GRID_HEIGHT = 54;

static inline bool in_bounds(int x, int y) {
    return x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<pair<int,int>> rabbitsList;
    static bool isRabbit[GRID_HEIGHT][GRID_WIDTH];
    for (int y = 0; y < GRID_HEIGHT; ++y) for (int x = 0; x < GRID_WIDTH; ++x) isRabbit[y][x] = false;

    int n;
    if (!(cin >> n)) return 0;
    rabbitsList.reserve(n);
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        if (in_bounds(x, y) && !isRabbit[y][x]) {
            isRabbit[y][x] = true;
            rabbitsList.emplace_back(x, y);
        }
    }

    static bool occupied[GRID_HEIGHT][GRID_WIDTH];
    static int segIndex[GRID_HEIGHT][GRID_WIDTH];
    static int distLayer[2][GRID_HEIGHT][GRID_WIDTH];
    static unsigned char firstDirLayer[2][GRID_HEIGHT][GRID_WIDTH];
    static int seenLayer[2][GRID_HEIGHT][GRID_WIDTH];
    int seenToken = 1;
    static int qx[GRID_WIDTH * GRID_HEIGHT];
    static int qy[GRID_WIDTH * GRID_HEIGHT];
    static unsigned char qg[GRID_WIDTH * GRID_HEIGHT];

    const int dx[4] = {1, 0, 0, -1};
    const int dy[4] = {0, -1, 1, 0};

    vector<pair<int,int>> lastOccupied;
    int turn = 0;
    while (true) {
        int ns;
        if (!(cin >> ns)) break;
        vector<pair<int,int>> snake(ns);
        for (int i = 0; i < ns; ++i) {
            int x, y;
            cin >> x >> y;
            snake[i] = {x, y};
        }
        ++turn;

        for (auto &p : lastOccupied) {
            int x = p.first, y = p.second;
            if (in_bounds(x, y)) {
                occupied[y][x] = false;
                segIndex[y][x] = -1;
            }
        }
        lastOccupied.clear();
        lastOccupied.reserve(ns);
        for (int i = 0; i < ns; ++i) {
            int x = snake[i].first;
            int y = snake[i].second;
            if (in_bounds(x, y)) { occupied[y][x] = true; segIndex[y][x] = i; }
            lastOccupied.emplace_back(x, y);
        }

        int headX = snake[0].first;
        int headY = snake[0].second;
        int tailX = snake.back().first;
        int tailY = snake.back().second;

        if (in_bounds(headX, headY) && isRabbit[headY][headX]) isRabbit[headY][headX] = false;

        auto isValidImmediate = [&](int dir)->bool{
            int nx = headX + dx[dir];
            int ny = headY + dy[dir];
            if (!in_bounds(nx, ny)) return false;
            if (!occupied[ny][nx]) return true;
            int k = segIndex[ny][nx];
            int ng = isRabbit[ny][nx] ? 1 : 0;
            int required = ns - k + ng;
            if (1 >= required) return true;
            return false;
        };

        int distToken = ++seenToken;
        int front = 0, back = 0;
        int dirCount[2][4] = {{0}};
        int bestDistDir[4];
        int cntBest[4] = {0,0,0,0};
        int cntBestPlus[4] = {0,0,0,0};
        for (int d = 0; d < 4; ++d) bestDistDir[d] = INT_MAX;
        int targetX = -1, targetY = -1, bestMD = INT_MAX;
        for (const auto& r : rabbitsList) {
            int rx = r.first, ry = r.second;
            if (!in_bounds(rx, ry)) continue;
            if (!isRabbit[ry][rx]) continue;
            int md = abs(rx - headX) + abs(ry - headY);
            if (md < bestMD) { bestMD = md; targetX = rx; targetY = ry; }
        }
        if (in_bounds(headX, headY)) {
            qx[back] = headX; qy[back] = headY; qg[back] = 0; ++back;
            distLayer[0][headY][headX] = 0;
            firstDirLayer[0][headY][headX] = 255;
            seenLayer[0][headY][headX] = distToken;
        }
        int chosenDir = -1;
        int chosenStage = 0;
        int expanded = 0;
        const int expandLimit = 1200;
        int bestFound = INT_MAX;
        int depthLimit = (bestMD == INT_MAX ? 16 : bestMD + 8);
        while (front < back && expanded <= expandLimit) {
            int cx = qx[front];
            int cy = qy[front];
            int cg = qg[front];
            ++front;
            int cd = distLayer[cg][cy][cx];
            ++expanded;
            if (bestFound != INT_MAX && cd > bestFound + 1) break;
            if (isRabbit[cy][cx]) {
                unsigned char fd = firstDirLayer[cg][cy][cx];
                if (fd < 4) {
                    if (cd < bestDistDir[fd]) { bestDistDir[fd] = cd; cntBest[fd] = 1; cntBestPlus[fd] = 0; }
                    else if (cd == bestDistDir[fd]) { ++cntBest[fd]; }
                    else if (cd == bestDistDir[fd] + 1) { ++cntBestPlus[fd]; }
                }
                if (cd < bestFound) bestFound = cd;
            }
            for (int d = 0; d < 4; ++d) {
                int nx = cx + dx[d];
                int ny = cy + dy[d];
                if (!in_bounds(nx, ny)) continue;
                int ng = cg;
                if (isRabbit[ny][nx]) ng = 1;
                bool blocked = false;
                if (occupied[ny][nx]) {
                    int k = segIndex[ny][nx];
                    if (!(nx == tailX && ny == tailY)) {
                        int required = ns - k + ng;
                        if (cd + 1 < required) blocked = true;
                    }
                }
                if (blocked) continue;
                if (cd + 1 > depthLimit) continue;
                if (seenLayer[ng][ny][nx] == distToken) continue;
                seenLayer[ng][ny][nx] = distToken;
                distLayer[ng][ny][nx] = cd + 1;
                firstDirLayer[ng][ny][nx] = (cd == 0 ? (unsigned char)d : firstDirLayer[cg][cy][cx]);
                unsigned char fd = firstDirLayer[ng][ny][nx];
                if (fd < 4) {
                    int nd = cd + 1;
                    int areaThresh = (bestFound == INT_MAX ? depthLimit : (bestFound + 1));
                    if (nd <= areaThresh) ++dirCount[ng][fd];
                }
                qx[back] = nx; qy[back] = ny; qg[back] = (unsigned char)ng; ++back;
            }
        }
        if (chosenDir == -1) {
            int totalDir[4];
            for (int d = 0; d < 4; ++d) totalDir[d] = dirCount[0][d] + dirCount[1][d];
            int bestD = INT_MAX, bestC1 = -1, bestC2 = -1, bestArea = -1, bestTie = INT_MAX, pick = -1;
            for (int d = 0; d < 4; ++d) if (isValidImmediate(d)) {
                int mdTie = targetX == -1 ? INT_MAX : abs(targetX - (headX + dx[d])) + abs(targetY - (headY + dy[d]));
                int bd = bestDistDir[d];
                int c1 = cntBest[d];
                int c2 = cntBestPlus[d];
                int area = totalDir[d];
                if (bd < bestD || (bd == bestD && (c1 > bestC1 || (c1 == bestC1 && (c2 > bestC2 || (c2 == bestC2 && (area > bestArea || (area == bestArea && mdTie < bestTie)))))))) {
                    bestD = bd; bestC1 = c1; bestC2 = c2; bestArea = area; bestTie = mdTie; pick = d;
                }
            }
            if (pick != -1 && bestD != INT_MAX) { chosenDir = pick; chosenStage = 1; }
        }

        

        if (chosenDir != -1 && !isValidImmediate(chosenDir)) chosenDir = -1;
        if (chosenDir == -1) {
            int totalDir[4];
            for (int d = 0; d < 4; ++d) totalDir[d] = dirCount[0][d] + dirCount[1][d];
            int bestArea = -1, bestTie = INT_MAX, pick = -1;
            for (int d = 0; d < 4; ++d) {
                if (!isValidImmediate(d)) continue;
                int nx = headX + dx[d];
                int ny = headY + dy[d];
                int tie = targetX == -1 ? INT_MAX : abs(targetX - nx) + abs(targetY - ny);
                int area = totalDir[d];
                if (area > bestArea || (area == bestArea && tie < bestTie)) { bestArea = area; bestTie = tie; pick = d; }
            }
            chosenDir = pick;
            if (chosenDir != -1) chosenStage = 2;
        }

        

        if (chosenDir == -1) {
            for (int d = 0; d < 4; ++d) {
                int nx = headX + dx[d];
                int ny = headY + dy[d];
                if (in_bounds(nx, ny)) { chosenDir = d; break; }
            }
            if (chosenDir == -1) chosenDir = 0;
            chosenStage = 3;
        }

        int nextX = headX + dx[chosenDir];
        int nextY = headY + dy[chosenDir];
        if (kDebug && (turn <= 5 || (turn % 25 == 0))) {
            int rabbitsLeft = 0;
            for (const auto& r : rabbitsList) if (in_bounds(r.first, r.second) && isRabbit[r.second][r.first]) ++rabbitsLeft;
            int totalDirSum[4];
            for (int d = 0; d < 4; ++d) totalDirSum[d] = dirCount[0][d] + dirCount[1][d];
            bool imm0 = isValidImmediate(0);
            bool imm1 = isValidImmediate(1);
            bool imm2 = isValidImmediate(2);
            bool imm3 = isValidImmediate(3);
            cerr << "t=" << turn
                 << " len=" << ns
                 << " head=" << headX << "," << headY
                 << " tail=" << tailX << "," << tailY
                 << " left=" << rabbitsLeft
                 << " target=" << targetX << "," << targetY
                 << " exp=" << expanded << "/" << 1200
                 << " best=[" << (bestDistDir[0]==INT_MAX?-1:bestDistDir[0]) << "," << (bestDistDir[1]==INT_MAX?-1:bestDistDir[1]) << "," << (bestDistDir[2]==INT_MAX?-1:bestDistDir[2]) << "," << (bestDistDir[3]==INT_MAX?-1:bestDistDir[3]) << "]"
                 << " c1=[" << cntBest[0] << "," << cntBest[1] << "," << cntBest[2] << "," << cntBest[3] << "]"
                 << " c2=[" << cntBestPlus[0] << "," << cntBestPlus[1] << "," << cntBestPlus[2] << "," << cntBestPlus[3] << "]"
                 << " area=[" << totalDirSum[0] << "," << totalDirSum[1] << "," << totalDirSum[2] << "," << totalDirSum[3] << "]"
                 << " imm=[" << (imm0?1:0) << "," << (imm1?1:0) << "," << (imm2?1:0) << "," << (imm3?1:0) << "]"
                 << " pick=" << chosenDir
                 << " stage=" << chosenStage
                 << " next=" << nextX << "," << nextY
                 << '\n';
        }
        cout << nextX << ' ' << nextY << endl;
    }

    return 0;
}