#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <memory>

using namespace std;

enum class BombType {
    A_BOMB,
    H_BOMB,
    B_BOMB
};

struct Position {
    int row, col;
    
    Position(int r, int c) : row(r), col(c) {}
    
    bool operator==(const Position& other) const {
        return row == other.row && col == other.col;
    }
};

struct Bomb {
    Position position;
    BombType type;
    bool hasExploded;
    
    Bomb(int r, int c, BombType t) : position(r, c), type(t), hasExploded(false) {}
};

class ExplosionGrid {
private:
    vector<vector<int>> grid;
    int size;
    
public:
    ExplosionGrid(int n) : size(n) {
        grid.assign(size, vector<int>(size, 0));
    }
    
    void setCell(int row, int col, int value) {
        if (isValidPosition(row, col)) {
            grid[row][col] = max(grid[row][col], value);
        }
    }
    
    int getCell(int row, int col) const {
        if (isValidPosition(row, col)) {
            return grid[row][col];
        }
        return 0;
    }
    
    void initializeFromInput(const vector<string>& inputGrid) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                char cell = inputGrid[i][j];
                if (cell >= '0' && cell <= '9') {
                    grid[i][j] = cell - '0';
                }
            }
        }
    }
    
    bool isValidPosition(int row, int col) const {
        return row >= 0 && row < size && col >= 0 && col < size;
    }
    
    int getSize() const { return size; }
    
    void displayGrid(const vector<Bomb>& bombs) const {
        vector<vector<char>> output(size, vector<char>(size));
        
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                output[i][j] = static_cast<char>('0' + grid[i][j]);
            }
        }
        
        for (const Bomb& bomb : bombs) {
            char bombChar = (bomb.type == BombType::A_BOMB) ? 'A' :
                           (bomb.type == BombType::H_BOMB) ? 'H' : 'B';
            output[bomb.position.row][bomb.position.col] = bombChar;
        }
        
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << output[i][j];
            }
            cout << endl;
        }
    }
};

class ExplosionPatternGenerator {
public:
    static void generateABombExplosion(ExplosionGrid& grid, const Position& center) {
        int maxDistance = 3;
        
        for (int dr = -maxDistance; dr <= maxDistance; dr++) {
            for (int dc = -maxDistance; dc <= maxDistance; dc++) {
                if (dr == 0 && dc == 0) continue;
                
                int distance = max(abs(dr), abs(dc));
                if (distance <= maxDistance) {
                    int intensity = maxDistance + 1 - distance;
                    grid.setCell(center.row + dr, center.col + dc, intensity);
                }
            }
        }
    }
    
    static void generateHBombExplosion(ExplosionGrid& grid, const Position& center) {
        int explosionRadius = 3;
        int intensity = 5;
        
        for (int dr = -explosionRadius; dr <= explosionRadius; dr++) {
            for (int dc = -explosionRadius; dc <= explosionRadius; dc++) {
                if (dr == 0 && dc == 0) continue;
                
                grid.setCell(center.row + dr, center.col + dc, intensity);
            }
        }
    }
    
    static void generateBBombExplosion(ExplosionGrid& grid, const Position& center) {
        int maxDistance = 3;
        
        for (int distance = 1; distance <= maxDistance; distance++) {
            int intensity = maxDistance + 1 - distance;
            
            grid.setCell(center.row - distance, center.col, intensity);
            grid.setCell(center.row + distance, center.col, intensity);
            grid.setCell(center.row, center.col - distance, intensity);
            grid.setCell(center.row, center.col + distance, intensity);
        }
    }
};

class BombDetector {
public:
    static vector<Bomb> extractBombs(const vector<string>& inputGrid) {
        vector<Bomb> bombs;
        
        for (int i = 0; i < static_cast<int>(inputGrid.size()); i++) {
            for (int j = 0; j < static_cast<int>(inputGrid[i].size()); j++) {
                char cell = inputGrid[i][j];
                
                if (cell == 'A') {
                    bombs.emplace_back(i, j, BombType::A_BOMB);
                } else if (cell == 'H') {
                    bombs.emplace_back(i, j, BombType::H_BOMB);
                } else if (cell == 'B') {
                    bombs.emplace_back(i, j, BombType::B_BOMB);
                }
            }
        }
        
        return bombs;
    }
    
    static vector<Bomb*> findTriggeredBBombs(vector<Bomb>& bombs, const ExplosionGrid& grid) {
        vector<Bomb*> triggeredBombs;
        
        for (Bomb& bomb : bombs) {
            if (bomb.type == BombType::B_BOMB && !bomb.hasExploded) {
                if (grid.getCell(bomb.position.row, bomb.position.col) > 0) {
                    triggeredBombs.push_back(&bomb);
                }
            }
        }
        
        return triggeredBombs;
    }
};

class ExplosionSimulator {
private:
    ExplosionGrid grid;
    vector<Bomb> bombs;
    
    void explodeInitialBombs() {
        for (Bomb& bomb : bombs) {
            if (bomb.type == BombType::A_BOMB || bomb.type == BombType::H_BOMB) {
                explodeBomb(bomb);
            }
        }
    }
    
    void explodeBomb(Bomb& bomb) {
        if (bomb.hasExploded) return;
        
        bomb.hasExploded = true;
        
        switch (bomb.type) {
            case BombType::A_BOMB:
                ExplosionPatternGenerator::generateABombExplosion(grid, bomb.position);
                break;
            case BombType::H_BOMB:
                ExplosionPatternGenerator::generateHBombExplosion(grid, bomb.position);
                break;
            case BombType::B_BOMB:
                ExplosionPatternGenerator::generateBBombExplosion(grid, bomb.position);
                break;
        }
    }
    
    void processChainReactions() {
        bool hasNewExplosions = true;
        
        while (hasNewExplosions) {
            vector<Bomb*> triggeredBombs = BombDetector::findTriggeredBBombs(bombs, grid);
            hasNewExplosions = !triggeredBombs.empty();
            
            for (Bomb* bomb : triggeredBombs) {
                explodeBomb(*bomb);
            }
        }
    }
    
public:
    ExplosionSimulator(int gridSize, const vector<string>& inputGrid) : grid(gridSize) {
        grid.initializeFromInput(inputGrid);
        bombs = BombDetector::extractBombs(inputGrid);
    }
    
    void simulateExplosions() {
        explodeInitialBombs();
        processChainReactions();
    }
    
    void displayResults() {
        grid.displayGrid(bombs);
    }
};

class InputProcessor {
public:
    static pair<int, vector<string>> readGridData() {
        int gridSize;
        cin >> gridSize;
        cin.ignore();
        
        vector<string> gridLines;
        gridLines.reserve(gridSize);
        
        for (int i = 0; i < gridSize; i++) {
            string line;
            getline(cin, line);
            gridLines.push_back(line);
        }
        
        return {gridSize, gridLines};
    }
};

class SweetSpotApplication {
private:
    unique_ptr<ExplosionSimulator> simulator;
    
public:
    void run() {
        auto [gridSize, gridData] = InputProcessor::readGridData();
        
        simulator = make_unique<ExplosionSimulator>(gridSize, gridData);
        simulator->simulateExplosions();
        simulator->displayResults();
    }
};

class ExplosionAnalyzer {
public:
    static int calculateTotalDamage(const ExplosionGrid& grid) {
        int totalDamage = 0;
        
        for (int i = 0; i < grid.getSize(); i++) {
            for (int j = 0; j < grid.getSize(); j++) {
                totalDamage += grid.getCell(i, j);
            }
        }
        
        return totalDamage;
    }
    
    static Position findMaximumIntensityPosition(const ExplosionGrid& grid) {
        int maxIntensity = 0;
        Position maxPosition(0, 0);
        
        for (int i = 0; i < grid.getSize(); i++) {
            for (int j = 0; j < grid.getSize(); j++) {
                if (grid.getCell(i, j) > maxIntensity) {
                    maxIntensity = grid.getCell(i, j);
                    maxPosition = Position(i, j);
                }
            }
        }
        
        return maxPosition;
    }
};

int main() {
    SweetSpotApplication app;
    app.run();
    
    return 0;
}
