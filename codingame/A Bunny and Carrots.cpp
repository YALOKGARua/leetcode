#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

enum class CellState {
    CARROT,
    EATEN
};

class CarrotGarden {
private:
    int height;
    int width;
    vector<vector<CellState>> grid;
    vector<int> topCarrotRow;
    
    void initializeGarden() {
        grid.assign(height, vector<CellState>(width, CellState::CARROT));
        topCarrotRow.assign(width, 0);
    }
    
public:
    CarrotGarden(int h, int w) : height(h), width(w) {
        initializeGarden();
    }
    
    bool eatCarrotFromColumn(int columnIndex) {
        int col = columnIndex - 1;
        
        if (col < 0 || col >= width) {
            return false;
        }
        
        if (topCarrotRow[col] >= height) {
            return false;
        }
        
        grid[topCarrotRow[col]][col] = CellState::EATEN;
        topCarrotRow[col]++;
        
        return true;
    }
    
    int calculatePerimeter() const {
        int perimeter = 0;
        
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                if (grid[row][col] == CellState::CARROT) {
                    perimeter += countExposedSides(row, col);
                }
            }
        }
        
        return perimeter;
    }
    
private:
    int countExposedSides(int row, int col) const {
        const int directions[][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        int exposedSides = 0;
        
        for (int i = 0; i < 4; i++) {
            int newRow = row + directions[i][0];
            int newCol = col + directions[i][1];
            
            if (isExposedSide(newRow, newCol)) {
                exposedSides++;
            }
        }
        
        return exposedSides;
    }
    
    bool isExposedSide(int row, int col) const {
        if (row < 0 || row >= height || col < 0 || col >= width) {
            return true;
        }
        
        return grid[row][col] == CellState::EATEN;
    }
};

class BunnySimulator {
private:
    unique_ptr<CarrotGarden> garden;
    vector<int> choices;
    vector<int> perimeterHistory;
    
public:
    BunnySimulator(int height, int width, const vector<int>& bunnyChoices) 
        : garden(make_unique<CarrotGarden>(height, width)), choices(bunnyChoices) {
        perimeterHistory.reserve(choices.size());
    }
    
    void simulateBunnyEating() {
        for (int choice : choices) {
            garden->eatCarrotFromColumn(choice);
            int currentPerimeter = garden->calculatePerimeter();
            perimeterHistory.push_back(currentPerimeter);
        }
    }
    
    const vector<int>& getPerimeterHistory() const {
        return perimeterHistory;
    }
};

class InputProcessor {
public:
    static pair<int, int> readGardenDimensions() {
        int height, width;
        cin >> height >> width;
        return {height, width};
    }
    
    static vector<int> readBunnyChoices() {
        int choiceCount;
        cin >> choiceCount;
        
        vector<int> choices;
        choices.reserve(choiceCount);
        
        for (int i = 0; i < choiceCount; i++) {
            int choice;
            cin >> choice;
            choices.push_back(choice);
        }
        
        return choices;
    }
};

class OutputFormatter {
public:
    static void displayPerimeters(const vector<int>& perimeters) {
        for (int perimeter : perimeters) {
            cout << perimeter << endl;
        }
    }
};

class BunnyCarrotApplication {
private:
    unique_ptr<BunnySimulator> simulator;
    
public:
    void run() {
        auto [height, width] = InputProcessor::readGardenDimensions();
        vector<int> choices = InputProcessor::readBunnyChoices();
        
        simulator = make_unique<BunnySimulator>(height, width, choices);
        simulator->simulateBunnyEating();
        
        const vector<int>& perimeterHistory = simulator->getPerimeterHistory();
        OutputFormatter::displayPerimeters(perimeterHistory);
    }
};

int main() {
    BunnyCarrotApplication app;
    app.run();
    
    return 0;
}
