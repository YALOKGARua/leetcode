#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct Position {
    int x, y;
    Position(int x = 0, int y = 0) : x(x), y(y) {}
    Position operator+(const Position& other) const {
        return Position(x + other.x, y + other.y);
    }
};

class TunnelNavigator {
private:
    vector<vector<int>> grid;
    int width, height;
    map<pair<int, string>, Position> roomTransitions;
    
    void initializeTransitions() {
        roomTransitions[{1, "TOP"}] = Position(0, 1);
        roomTransitions[{1, "LEFT"}] = Position(0, 1);
        roomTransitions[{1, "RIGHT"}] = Position(0, 1);
        
        roomTransitions[{2, "LEFT"}] = Position(1, 0);
        roomTransitions[{2, "RIGHT"}] = Position(-1, 0);
        
        roomTransitions[{3, "TOP"}] = Position(0, 1);
        
        roomTransitions[{4, "TOP"}] = Position(-1, 0);
        roomTransitions[{4, "RIGHT"}] = Position(0, 1);
        
        roomTransitions[{5, "TOP"}] = Position(1, 0);
        roomTransitions[{5, "LEFT"}] = Position(0, 1);
        
        roomTransitions[{6, "LEFT"}] = Position(1, 0);
        roomTransitions[{6, "RIGHT"}] = Position(-1, 0);
        
        roomTransitions[{7, "TOP"}] = Position(0, 1);
        roomTransitions[{7, "RIGHT"}] = Position(0, 1);
        
        roomTransitions[{8, "LEFT"}] = Position(0, 1);
        roomTransitions[{8, "RIGHT"}] = Position(0, 1);
        
        roomTransitions[{9, "TOP"}] = Position(0, 1);
        roomTransitions[{9, "LEFT"}] = Position(0, 1);
        
        roomTransitions[{10, "TOP"}] = Position(-1, 0);
        
        roomTransitions[{11, "TOP"}] = Position(1, 0);
        
        roomTransitions[{12, "RIGHT"}] = Position(0, 1);
        
        roomTransitions[{13, "LEFT"}] = Position(0, 1);
    }
    
public:
    TunnelNavigator(int w, int h) : width(w), height(h), grid(h, vector<int>(w)) {
        initializeTransitions();
    }
    
    void setGrid(const vector<vector<int>>& newGrid) {
        grid = newGrid;
    }
    
    Position getNextPosition(int x, int y, const string& entrance) {
        if (x < 0 || x >= width || y < 0 || y >= height) {
            return Position(-1, -1);
        }
        
        int roomType = grid[y][x];
        auto key = make_pair(roomType, entrance);
        
        if (roomTransitions.find(key) != roomTransitions.end()) {
            Position delta = roomTransitions[key];
            Position nextPos = Position(x, y) + delta;
            
            if (nextPos.x >= 0 && nextPos.x < width && 
                nextPos.y >= 0 && nextPos.y < height) {
                return nextPos;
            }
        }
        
        return Position(-1, -1);
    }
};

int main() {
    int w, h;
    cin >> w >> h;
    cin.ignore();
    
    TunnelNavigator navigator(w, h);
    vector<vector<int>> grid(h, vector<int>(w));
    
    for (int i = 0; i < h; i++) {
        string line;
        getline(cin, line);
        
        vector<string> tokens;
        string token = "";
        for (char c : line) {
            if (c == ' ') {
                if (!token.empty()) {
                    tokens.push_back(token);
                    token = "";
                }
            } else {
                token += c;
            }
        }
        if (!token.empty()) {
            tokens.push_back(token);
        }
        
        for (int j = 0; j < w && j < tokens.size(); j++) {
            grid[i][j] = stoi(tokens[j]);
        }
    }
    
    navigator.setGrid(grid);
    
    int ex;
    cin >> ex;
    cin.ignore();
    
    while (true) {
        int xi, yi;
        string pos;
        cin >> xi >> yi >> pos;
        cin.ignore();
        
        Position nextPos = navigator.getNextPosition(xi, yi, pos);
        cout << nextPos.x << " " << nextPos.y << endl;
    }
    
    return 0;
}
