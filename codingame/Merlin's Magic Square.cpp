#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class MerlinSquare {
private:
    vector<vector<bool>> grid;
    
public:
    MerlinSquare() : grid(3, vector<bool>(3, false)) {}
    
    void parseState(const string& row1, const string& row2, const string& row3) {
        parseRow(row1, 0);
        parseRow(row2, 1);
        parseRow(row3, 2);
    }
    
    void parseRow(const string& row, int rowIndex) {
        for (int i = 0; i < 3; i++) {
            grid[rowIndex][i] = (row[i * 2] == '*');
        }
    }
    
    void flip(int row, int col) {
        if (row >= 0 && row < 3 && col >= 0 && col < 3) {
            grid[row][col] = !grid[row][col];
        }
    }
    
    void pressButton(int button) {
        switch (button) {
            case 1: // Top-left corner
                flip(0, 0); flip(0, 1); flip(1, 0); flip(1, 1);
                break;
            case 2: // Top side
                flip(0, 0); flip(0, 1); flip(0, 2);
                break;
            case 3: // Top-right corner
                flip(0, 1); flip(0, 2); flip(1, 1); flip(1, 2);
                break;
            case 4: // Left side
                flip(0, 0); flip(1, 0); flip(2, 0);
                break;
            case 5: // Center
                flip(0, 1); flip(1, 0); flip(1, 1); flip(1, 2); flip(2, 1);
                break;
            case 6: // Right side
                flip(0, 2); flip(1, 2); flip(2, 2);
                break;
            case 7: // Bottom-left corner
                flip(1, 0); flip(1, 1); flip(2, 0); flip(2, 1);
                break;
            case 8: // Bottom side
                flip(2, 0); flip(2, 1); flip(2, 2);
                break;
            case 9: // Bottom-right corner
                flip(1, 1); flip(1, 2); flip(2, 1); flip(2, 2);
                break;
        }
    }
    
    bool isSolved() const {
        vector<vector<bool>> target = {
            {true, true, true},
            {true, false, true},
            {true, true, true}
        };
        return grid == target;
    }
    
    MerlinSquare copy() const {
        MerlinSquare newSquare;
        newSquare.grid = grid;
        return newSquare;
    }
};

int main() {
    string row1, row2, row3, buttons;
    getline(cin, row1);
    getline(cin, row2);
    getline(cin, row3);
    getline(cin, buttons);
    
    MerlinSquare square;
    square.parseState(row1, row2, row3);
    
    for (char c : buttons) {
        int button = c - '0';
        square.pressButton(button);
    }
    
    for (int finalButton = 1; finalButton <= 9; finalButton++) {
        MerlinSquare testSquare = square.copy();
        testSquare.pressButton(finalButton);
        
        if (testSquare.isSolved()) {
            cout << finalButton << endl;
            return 0;
        }
    }
    
    return 0;
}
