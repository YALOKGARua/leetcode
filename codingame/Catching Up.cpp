#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
using namespace std;

struct Position {
    int y, x;
    Position(int y = 0, int x = 0) : y(y), x(x) {}
    bool operator==(const Position& other) const {
        return y == other.y && x == other.x;
    }
    bool operator<(const Position& other) const {
        return y < other.y || (y == other.y && x < other.x);
    }
};

vector<string> grid;
Position player;
int k;

int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};
char moves[4] = {'U', 'D', 'L', 'R'};

bool isValid(int y, int x) {
    return y >= 0 && y < 10 && x >= 0 && x < 10 && grid[y][x] != '*';
}

int distance(const Position& a, const Position& b) {
    return abs(a.y - b.y) + abs(a.x - b.x);
}

bool isAdjacent(const Position& a, const Position& b) {
    return distance(a, b) == 1;
}

Position enemyMove(const Position& enemy, const Position& playerPos) {
    Position best = enemy;
    int maxDist = distance(enemy, playerPos);
    
    for (int i = 0; i < 4; i++) {
        int ny = enemy.y + dy[i];
        int nx = enemy.x + dx[i];
        if (isValid(ny, nx)) {
            int d = distance(Position(ny, nx), playerPos);
            if (d > maxDist) {
                maxDist = d;
                best = Position(ny, nx);
            }
        }
    }
    return best;
}

char bfs(const Position& start, const Position& enemy, int turn) {
    struct State {
        Position player, enemy;
        int turn;
        vector<int> path;
    };
    
    map<tuple<Position, Position, int>, bool> visited;
    queue<State> q;
    q.push({start, enemy, turn, {}});
    visited[{start, enemy, turn % k}] = true;
    
    while (!q.empty()) {
        State s = q.front();
        q.pop();
        
        if (isAdjacent(s.player, s.enemy)) {
            if (s.path.empty()) return 'U';
            return moves[s.path[0]];
        }
        
        for (int i = 0; i < 4; i++) {
            int ny = s.player.y + dy[i];
            int nx = s.player.x + dx[i];
            if (!isValid(ny, nx)) continue;
            
            Position newPlayer(ny, nx);
            Position newEnemy = s.enemy;
            int newTurn = s.turn + 1;
            
            if (newTurn % k == 1) {
                newEnemy = enemyMove(s.enemy, newPlayer);
            }
            
            auto key = make_tuple(newPlayer, newEnemy, newTurn % k);
            if (visited.find(key) == visited.end()) {
                visited[key] = true;
                vector<int> new_path = s.path;
                new_path.push_back(i);
                q.push({newPlayer, newEnemy, newTurn, new_path});
            }
        }
    }
    
    for (int i = 0; i < 4; i++) {
        int ny = start.y + dy[i];
        int nx = start.x + dx[i];
        if (isValid(ny, nx)) return moves[i];
    }
    return 'U';
}

int main() {
    cin >> k;
    cin.ignore();
    grid.resize(10);
    for (int i = 0; i < 10; i++) {
        getline(cin, grid[i]);
        for (int j = 0; j < 10; j++) {
            if (grid[i][j] == 'P') {
                player = Position(i, j);
                grid[i][j] = '-';
            }
        }
    }
    
    int turn = 0;
    while (true) {
        int ene_y, ene_x;
        cin >> ene_y >> ene_x;
        cin.ignore();
        Position enemy(ene_y, ene_x);
        
        for (int i = 0; i < 4; i++) {
            int ny = player.y + dy[i];
            int nx = player.x + dx[i];
            if (isValid(ny, nx) && isAdjacent(Position(ny, nx), enemy)) {
                player.y = ny;
                player.x = nx;
                cout << moves[i] << endl;
                turn++;
                continue;
            }
        }
        
        char move = bfs(player, enemy, turn);
        for (int i = 0; i < 4; i++) {
            if (move == moves[i]) {
                player.y += dy[i];
                player.x += dx[i];
                break;
            }
        }
        turn++;
        cout << move << endl;
    }
    return 0;
}