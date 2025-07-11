#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <sstream>

using namespace std;

enum Direction { TOP, LEFT, RIGHT };
enum RoomType { VERTICAL = 1, HORIZONTAL = 2, CORNER_DR = 3, CORNER_DL = 4, CORNER_UR = 5, 
                CORNER_UL = 6, T_DOWN = 7, T_RIGHT = 8, T_LEFT = 9, CROSS = 10, T_UP = 11, 
                VERTICAL_RIGHT = 12, VERTICAL_LEFT = 13 };

struct Position {
    int x, y;
    Direction dir;
    
    bool operator<(const Position& other) const {
        return tie(x, y, dir) < tie(other.x, other.y, other.dir);
    }
    
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y && dir == other.dir;
    }
};

struct Rock {
    int x, y;
    Direction dir;
};

class TunnelSimulator {
private:
    int width, height, exit_x;
    vector<vector<int>> original_grid;
    vector<vector<int>> current_grid;
    set<pair<int, int>> recently_rotated;
    
    map<int, map<Direction, pair<int, int>>> room_exits = {
        {1, {{TOP, {0, 1}}}},
        {2, {{TOP, {0, 1}}, {LEFT, {1, 0}}, {RIGHT, {-1, 0}}}},
        {3, {{TOP, {0, 1}}, {LEFT, {1, 0}}}},
        {4, {{TOP, {-1, 0}}, {RIGHT, {0, 1}}}},
        {5, {{RIGHT, {0, 1}}, {TOP, {1, 0}}}},
        {6, {{LEFT, {0, 1}}, {TOP, {-1, 0}}}},
        {7, {{TOP, {0, 1}}, {LEFT, {1, 0}}, {RIGHT, {-1, 0}}}},
        {8, {{TOP, {0, 1}}, {RIGHT, {-1, 0}}}},
        {9, {{TOP, {0, 1}}, {LEFT, {1, 0}}}},
        {10, {{TOP, {0, 1}}, {LEFT, {1, 0}}, {RIGHT, {-1, 0}}}},
        {11, {{TOP, {1, 0}}, {LEFT, {1, 0}}, {RIGHT, {-1, 0}}}},
        {12, {{TOP, {0, 1}}, {RIGHT, {-1, 0}}}},
        {13, {{TOP, {0, 1}}, {LEFT, {0, 1}}}}
    };
    
public:
    TunnelSimulator(int w, int h, int ex, const vector<vector<int>>& grid) 
        : width(w), height(h), exit_x(ex), original_grid(grid), current_grid(grid) {}
    
    bool can_rotate(int x, int y) {
        return current_grid[y][x] > 0;
    }
    
    void rotate_room(int x, int y, bool clockwise) {
        if (!can_rotate(x, y)) return;
        
        int room_type = abs(current_grid[y][x]);
        
        if (clockwise) {
            switch (room_type) {
                case 1: current_grid[y][x] = 2; break;
                case 2: current_grid[y][x] = 1; break;
                case 3: current_grid[y][x] = 6; break;
                case 4: current_grid[y][x] = 3; break;
                case 5: current_grid[y][x] = 4; break;
                case 6: current_grid[y][x] = 5; break;
                case 7: current_grid[y][x] = 9; break;
                case 8: current_grid[y][x] = 7; break;
                case 9: current_grid[y][x] = 11; break;
                case 11: current_grid[y][x] = 8; break;
                case 12: current_grid[y][x] = 13; break;
                case 13: current_grid[y][x] = 12; break;
                default: break;
            }
        } else {
            switch (room_type) {
                case 1: current_grid[y][x] = 2; break;
                case 2: current_grid[y][x] = 1; break;
                case 3: current_grid[y][x] = 4; break;
                case 4: current_grid[y][x] = 5; break;
                case 5: current_grid[y][x] = 6; break;
                case 6: current_grid[y][x] = 3; break;
                case 7: current_grid[y][x] = 8; break;
                case 8: current_grid[y][x] = 11; break;
                case 9: current_grid[y][x] = 7; break;
                case 11: current_grid[y][x] = 9; break;
                case 12: current_grid[y][x] = 13; break;
                case 13: current_grid[y][x] = 12; break;
                default: break;
            }
        }
    }
    
    Position move_entity(const Position& pos) {
        int room_type = abs(current_grid[pos.y][pos.x]);
        
        if (room_exits[room_type].find(pos.dir) == room_exits[room_type].end()) {
            return {-1, -1, TOP};
        }
        
        auto [dx, dy] = room_exits[room_type][pos.dir];
        
        int new_x = pos.x + dx;
        int new_y = pos.y + dy;
        
        if (new_x < 0 || new_x >= width || new_y < 0 || new_y >= height) {
            return {-1, -1, TOP};
        }
        
        Direction new_dir = TOP;
        if (dx == 0 && dy == 1) new_dir = TOP;
        else if (dx == 1 && dy == 0) new_dir = LEFT;
        else if (dx == -1 && dy == 0) new_dir = RIGHT;
        else if (dx == 0 && dy == -1) new_dir = TOP;
        
        cerr << "MOVEMENT: (" << pos.x << "," << pos.y << ") dir=" << pos.dir 
             << " room=" << room_type << " move_delta=(" << dx << "," << dy 
             << ") -> (" << new_x << "," << new_y << ") new_dir=" << new_dir << endl;
        
        return {new_x, new_y, new_dir};
    }
    
    bool has_path_to_exit(const Position& start) {
        queue<Position> q;
        set<Position> visited;
        
        q.push(start);
        visited.insert(start);
        
        while (!q.empty()) {
            Position current = q.front();
            q.pop();
            
            if (current.y == height - 1 && current.x == exit_x) {
                return true;
            }
            
            Position next = move_entity(current);
            if (next.x != -1 && visited.find(next) == visited.end()) {
                visited.insert(next);
                q.push(next);
            }
        }
        
        return false;
    }
    
    vector<Rock> simulate_rocks(const vector<Rock>& rocks) {
        vector<Rock> new_rocks;
        
        for (const auto& rock : rocks) {
            Position rock_pos = {rock.x, rock.y, rock.dir};
            Position next_pos = move_entity(rock_pos);
            
            if (next_pos.x != -1) {
                new_rocks.push_back({next_pos.x, next_pos.y, next_pos.dir});
            }
        }
        
        map<pair<int, int>, int> position_count;
        for (const auto& rock : new_rocks) {
            position_count[{rock.x, rock.y}]++;
        }
        
        vector<Rock> surviving_rocks;
        for (const auto& rock : new_rocks) {
            if (position_count[{rock.x, rock.y}] == 1) {
                surviving_rocks.push_back(rock);
            }
        }
        
        return surviving_rocks;
    }
    
    bool is_safe_path(const Position& indy_pos, const vector<Rock>& rocks, int steps_ahead = 3) {
        Position current_indy = indy_pos;
        vector<Rock> current_rocks = rocks;
        
        for (int step = 0; step < steps_ahead; step++) {
            current_indy = move_entity(current_indy);
            if (current_indy.x == -1) return false;
            
            current_rocks = simulate_rocks(current_rocks);
            
            for (const auto& rock : current_rocks) {
                if (rock.x == current_indy.x && rock.y == current_indy.y) {
                    return false;
                }
            }
            
            if (current_indy.y == height - 1 && current_indy.x == exit_x) {
                return true;
            }
        }
        
        return has_path_to_exit(current_indy);
    }
    
    string find_best_move(const Position& indy_pos, const vector<Rock>& rocks) {
        Position next_pos = move_entity(indy_pos);
        
        cerr << "Indy at (" << indy_pos.x << "," << indy_pos.y << ") dir=" << indy_pos.dir 
             << " room_type=" << abs(current_grid[indy_pos.y][indy_pos.x]) << endl;
        
        // Detailed room analysis
        int current_room = abs(current_grid[indy_pos.y][indy_pos.x]);
        if (room_exits.find(current_room) != room_exits.end()) {
            cerr << "Room " << current_room << " exits: ";
            for (auto& exit : room_exits[current_room]) {
                cerr << "dir" << exit.first << "->(" << exit.second.first << "," << exit.second.second << ") ";
            }
            cerr << endl;
        }
        
        if (next_pos.x == -1) {
            cerr << "BLOCKED! Searching for emergency rotation..." << endl;
            
            for (int search_radius = 1; search_radius <= 5; search_radius++) {
                for (int dy = -search_radius; dy <= search_radius; dy++) {
                    for (int dx = -search_radius; dx <= search_radius; dx++) {
                        int nx = indy_pos.x + dx;
                        int ny = indy_pos.y + dy;
                        
                        if (nx >= 0 && nx < width && ny >= 0 && ny < height && 
                            can_rotate(nx, ny) && !(nx == indy_pos.x && ny == indy_pos.y) &&
                            recently_rotated.find({nx, ny}) == recently_rotated.end()) {
                            
                            vector<bool> rotations = {true, false};
                            for (bool clockwise : rotations) {
                                int original_room = current_grid[ny][nx];
                                
                                rotate_room(nx, ny, clockwise);
                                Position test_pos = move_entity(indy_pos);
                                
                                                            if (test_pos.x != -1) {
                                cerr << "EMERGENCY FIX: rotate (" << nx << "," << ny << ") " 
                                     << (clockwise ? "RIGHT" : "LEFT") 
                                     << " unblocks to (" << test_pos.x << "," << test_pos.y << ")" << endl;
                                current_grid[ny][nx] = original_room;
                                return to_string(nx) + " " + to_string(ny) + " " + 
                                       (clockwise ? "RIGHT" : "LEFT");
                            }
                                
                                current_grid[ny][nx] = original_room;
                            }
                        }
                    }
                }
            }
        } else {
            cerr << "Can move to (" << next_pos.x << "," << next_pos.y << ") dir=" << next_pos.dir << endl;
        
        if (next_pos.x >= 0 && next_pos.x < width && next_pos.y >= 0 && next_pos.y < height) {
            int dest_room = current_grid[next_pos.y][next_pos.x];
            cerr << "Destination room value: " << dest_room << " (abs=" << abs(dest_room) << ")" << endl;
            if (dest_room == 0) {
                cerr << "WARNING: Trying to enter empty space/wall!" << endl;
            }
        }
            
                        if (next_pos.x >= 0 && next_pos.x < width && next_pos.y >= 0 && next_pos.y < height) {
                int next_room_type = abs(current_grid[next_pos.y][next_pos.x]);
                cerr << "Next room type: " << next_room_type << endl;
                
                if (room_exits[next_room_type].find(next_pos.dir) == room_exits[next_room_type].end()) {
                    cerr << "CRITICAL: Next room " << next_room_type << " doesn't support direction " << next_pos.dir << "!" << endl;
                    
                    Position problem_pos = next_pos;
                    Position test_after = move_entity(problem_pos);
                    if (test_after.x == -1) {
                        cerr << "Looking ahead - next position will be blocked!" << endl;
                        
                        for (int dy = 0; dy <= 2; dy++) {
                            for (int dx = -1; dx <= 1; dx++) {
                                int nx = problem_pos.x + dx;
                                int ny = problem_pos.y + dy;
                                
                                if (nx >= 0 && nx < width && ny >= 0 && ny < height && 
                                    can_rotate(nx, ny) && !(nx == indy_pos.x && ny == indy_pos.y) &&
                                    recently_rotated.find({nx, ny}) == recently_rotated.end()) {
                                    
                                    vector<bool> rotations = {true, false};
                                    for (bool clockwise : rotations) {
                                        int original_room = current_grid[ny][nx];
                                        
                                        rotate_room(nx, ny, clockwise);
                                        Position retest = move_entity(problem_pos);
                                        
                                        if (retest.x != -1) {
                                            cerr << "CRITICAL FIX: rotate (" << nx << "," << ny << ") " 
                                                 << (clockwise ? "RIGHT" : "LEFT") 
                                                 << " fixes incompatible room!" << endl;
                                            current_grid[ny][nx] = original_room;
                                            return to_string(nx) + " " + to_string(ny) + " " + 
                                                   (clockwise ? "RIGHT" : "LEFT");
                                        }
                                        
                                        current_grid[ny][nx] = original_room;
                                    }
                                }
                            }
                        }
                    }
                } else {
                    Position test_after = move_entity(next_pos);
                    cerr << "From (" << next_pos.x << "," << next_pos.y << ") dir=" << next_pos.dir 
                         << " room=" << next_room_type << " would go to (" 
                         << test_after.x << "," << test_after.y << ")" << endl;
                }
            }
            
            cerr << "Looking for strategic rotation..." << endl;
            
            for (int search_dist = 1; search_dist <= 3; search_dist++) {
                for (int dy = -search_dist; dy <= search_dist; dy++) {
                    for (int dx = -search_dist; dx <= search_dist; dx++) {
                        int nx = indy_pos.x + dx;
                        int ny = indy_pos.y + dy;
                        
                        if (nx >= 0 && nx < width && ny >= 0 && ny < height && 
                            can_rotate(nx, ny) && !(nx == indy_pos.x && ny == indy_pos.y) && 
                            !(nx == next_pos.x && ny == next_pos.y) &&
                            recently_rotated.find({nx, ny}) == recently_rotated.end()) {
                            
                            vector<bool> rotations = {true, false};
                            for (bool clockwise : rotations) {
                                int original_room = current_grid[ny][nx];
                                
                                rotate_room(nx, ny, clockwise);
                                Position test_move = move_entity(indy_pos);
                                
                                if (test_move.x != -1) {
                                    Position test_future = move_entity(test_move);
                                    if (test_future.x != -1 || test_move.y == height - 1 || test_move.y > indy_pos.y) {
                                        cerr << "SMART FIX: rotate (" << nx << "," << ny << ") " 
                                             << (clockwise ? "RIGHT" : "LEFT") 
                                             << " creates path (" << indy_pos.x << "," << indy_pos.y 
                                             << ") -> (" << test_move.x << "," << test_move.y 
                                             << ") -> (" << test_future.x << "," << test_future.y << ")" << endl;
                                        
                                        Position final_check = move_entity(indy_pos);
                                        cerr << "POST-ROTATION CHECK: Indy would actually go to (" 
                                             << final_check.x << "," << final_check.y << ") dir=" << final_check.dir << endl;
                                        
                                        if (final_check.x == next_pos.x && final_check.y == next_pos.y) {
                                            cerr << "GOOD: Rotation doesn't change Indy's immediate path" << endl;
                                        } else {
                                            cerr << "WARNING: Rotation changed Indy's path from (" << next_pos.x 
                                                 << "," << next_pos.y << ") to (" << final_check.x << "," << final_check.y << ")" << endl;
                                        }
                                        
                                        current_grid[ny][nx] = original_room;
                                        return to_string(nx) + " " + to_string(ny) + " " + 
                                               (clockwise ? "RIGHT" : "LEFT");
                                    }
                                }
                                
                                current_grid[ny][nx] = original_room;
                            }
                        }
                    }
                }
            }
        }
        
        cerr << "CRITICAL: No rotation found! Grid around Indy:" << endl;
        for (int dy = -2; dy <= 2; dy++) {
            for (int dx = -2; dx <= 2; dx++) {
                int nx = indy_pos.x + dx;
                int ny = indy_pos.y + dy;
                if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                    cerr << "(" << nx << "," << ny << ")=" << current_grid[ny][nx] 
                         << (can_rotate(nx, ny) ? "R" : "F") << " ";
                } else {
                    cerr << "OOB ";
                }
            }
            cerr << endl;
        }
        return "WAIT";
    }
    
    void apply_move(const string& move) {
        if (move != "WAIT") {
            stringstream ss(move);
            string x_str, y_str, direction;
            ss >> x_str >> y_str >> direction;
            
            int x = stoi(x_str);
            int y = stoi(y_str);
            bool clockwise = (direction == "RIGHT");
            
            int old_room = current_grid[y][x];
            rotate_room(x, y, clockwise);
            int new_room = current_grid[y][x];
            
            cerr << "APPLIED: Rotated (" << x << "," << y << ") " << direction 
                 << " from room " << old_room << " to room " << new_room << endl;
            
            recently_rotated.insert({x, y});
            
            if (recently_rotated.size() > 5) {
                recently_rotated.clear();
            }
        }
    }
};

Direction parse_direction(const string& dir) {
    if (dir == "TOP") return TOP;
    if (dir == "LEFT") return LEFT;
    return RIGHT;
}

int main() {
    int w, h;
    cin >> w >> h;
    cin.ignore();
    
    vector<vector<int>> grid(h, vector<int>(w));
    for (int i = 0; i < h; i++) {
        string line;
        getline(cin, line);
        stringstream ss(line);
        for (int j = 0; j < w; j++) {
            ss >> grid[i][j];
        }
    }
    
    int ex;
    cin >> ex;
    cin.ignore();
    
    TunnelSimulator simulator(w, h, ex, grid);
    
    while (true) {
        int xi, yi;
        string posi;
        cin >> xi >> yi >> posi;
        cin.ignore();
        
        Position indy_pos = {xi, yi, parse_direction(posi)};
        
        int r;
        cin >> r;
        cin.ignore();
        
        vector<Rock> rocks(r);
        for (int i = 0; i < r; i++) {
            int xr, yr;
            string posr;
            cin >> xr >> yr >> posr;
            cin.ignore();
            rocks[i] = {xr, yr, parse_direction(posr)};
        }
        
        string move = simulator.find_best_move(indy_pos, rocks);
        cout << move << endl;
        simulator.apply_move(move);
    }
    
    return 0;
}
