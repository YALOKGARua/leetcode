#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const int sizeN = 15;
    while (true) {
        vector<vector<int>> board(sizeN, vector<int>(sizeN));
        for (int i = 0; i < sizeN; i++) {
            for (int j = 0; j < sizeN; j++) {
                int color;
                if (!(cin >> color)) return 0;
                board[i][j] = color;
            }
        }

        vector<vector<char>> visited(sizeN, vector<char>(sizeN, 0));
        int bestClusterSize = 0;
        pair<int, int> bestCell = {0, sizeN - 1};
        const int di[4] = {1, -1, 0, 0};
        const int dj[4] = {0, 0, 1, -1};

        for (int i = 0; i < sizeN; i++) {
            for (int j = 0; j < sizeN; j++) {
                if (visited[i][j]) continue;
                int color = board[i][j];
                if (color < 0) continue;
                queue<pair<int, int>> q;
                q.push({i, j});
                visited[i][j] = 1;
                vector<pair<int, int>> cells;
                while (!q.empty()) {
                    auto [ci, cj] = q.front();
                    q.pop();
                    cells.push_back({ci, cj});
                    for (int d = 0; d < 4; d++) {
                        int ni = ci + di[d];
                        int nj = cj + dj[d];
                        if (ni < 0 || ni >= sizeN || nj < 0 || nj >= sizeN) continue;
                        if (visited[ni][nj]) continue;
                        if (board[ni][nj] != color) continue;
                        visited[ni][nj] = 1;
                        q.push({ni, nj});
                    }
                }
                if ((int)cells.size() < 2) continue;
                pair<int, int> representative = cells[0];
                for (auto &p : cells) {
                    if (p.first > representative.first || (p.first == representative.first && p.second < representative.second)) representative = p;
                }
                if ((int)cells.size() > bestClusterSize) {
                    bestClusterSize = (int)cells.size();
                    bestCell = representative;
                } else if ((int)cells.size() == bestClusterSize) {
                    if (representative.first > bestCell.first || (representative.first == bestCell.first && representative.second < bestCell.second)) bestCell = representative;
                }
            }
        }

        if (bestClusterSize >= 2) {
            int outCol = bestCell.second;
            int outRow = sizeN - 1 - bestCell.first;
            cout << outCol << ' ' << outRow << endl;
        } else {
            cout << 0 << ' ' << 0 << endl;
        }
    }
}