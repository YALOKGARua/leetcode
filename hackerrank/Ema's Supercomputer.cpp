#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

class PlusShapeAnalyzer {
private:
    struct PlusConfiguration {
        int centerRow, centerColumn, armLength;
        int area;
        
        PlusConfiguration(int row, int col, int length) 
            : centerRow(row), centerColumn(col), armLength(length) {
            area = 4 * length + 1;
        }
    };
    
    static int calculateMaximumPlusSize(const vector<string>& grid, int centerRow, int centerCol) {
        int gridHeight = grid.size();
        int gridWidth = grid[0].size();
        int maxArmLength = 0;
        
        while (true) {
            bool canExtendPlus = true;
            
            if (centerRow - maxArmLength - 1 < 0 || centerRow + maxArmLength + 1 >= gridHeight ||
                centerCol - maxArmLength - 1 < 0 || centerCol + maxArmLength + 1 >= gridWidth) {
                canExtendPlus = false;
            }
            
            if (canExtendPlus) {
                if (grid[centerRow - maxArmLength - 1][centerCol] != 'G' ||
                    grid[centerRow + maxArmLength + 1][centerCol] != 'G' ||
                    grid[centerRow][centerCol - maxArmLength - 1] != 'G' ||
                    grid[centerRow][centerCol + maxArmLength + 1] != 'G') {
                    canExtendPlus = false;
                }
            }
            
            if (!canExtendPlus) {
                break;
            }
            
            maxArmLength++;
        }
        
        return maxArmLength;
    }
    
    static vector<PlusConfiguration> generateAllValidPluses(const vector<string>& gameGrid) {
        vector<PlusConfiguration> validPluses;
        int rows = gameGrid.size();
        int columns = gameGrid[0].size();
        
        for (int rowIndex = 0; rowIndex < rows; ++rowIndex) {
            for (int columnIndex = 0; columnIndex < columns; ++columnIndex) {
                if (gameGrid[rowIndex][columnIndex] == 'G') {
                    int maxPlusSize = calculateMaximumPlusSize(gameGrid, rowIndex, columnIndex);
                    
                    for (int armSize = 0; armSize <= maxPlusSize; ++armSize) {
                        validPluses.emplace_back(rowIndex, columnIndex, armSize);
                    }
                }
            }
        }
        
        return validPluses;
    }
    
    static bool doPluszesOverlap(const PlusConfiguration& firstPlus, const PlusConfiguration& secondPlus) {
        set<pair<int, int>> firstPlusOccupiedCells;
        set<pair<int, int>> secondPlusOccupiedCells;
        
        auto addPlusCellsToSet = [](const PlusConfiguration& plus, set<pair<int, int>>& cellSet) {
            cellSet.insert({plus.centerRow, plus.centerColumn});
            
            for (int armIndex = 1; armIndex <= plus.armLength; ++armIndex) {
                cellSet.insert({plus.centerRow - armIndex, plus.centerColumn});
                cellSet.insert({plus.centerRow + armIndex, plus.centerColumn});
                cellSet.insert({plus.centerRow, plus.centerColumn - armIndex});
                cellSet.insert({plus.centerRow, plus.centerColumn + armIndex});
            }
        };
        
        addPlusCellsToSet(firstPlus, firstPlusOccupiedCells);
        addPlusCellsToSet(secondPlus, secondPlusOccupiedCells);
        
        for (const auto& cell : firstPlusOccupiedCells) {
            if (secondPlusOccupiedCells.count(cell)) {
                return true;
            }
        }
        
        return false;
    }
    
public:
    static int findMaximumPlusProduct(const vector<string>& gridConfiguration) {
        vector<PlusConfiguration> allPossiblePluses = generateAllValidPluses(gridConfiguration);
        int maximumProduct = 1;
        
        for (int firstPlusIndex = 0; firstPlusIndex < allPossiblePluses.size(); ++firstPlusIndex) {
            for (int secondPlusIndex = firstPlusIndex + 1; secondPlusIndex < allPossiblePluses.size(); ++secondPlusIndex) {
                const auto& plus1 = allPossiblePluses[firstPlusIndex];
                const auto& plus2 = allPossiblePluses[secondPlusIndex];
                
                if (!doPluszesOverlap(plus1, plus2)) {
                    maximumProduct = max(maximumProduct, plus1.area * plus2.area);
                }
            }
        }
        
        return maximumProduct;
    }
};

class OptimizedPlusSearchEngine {
private:
    struct Plus {
        int row, col, size, area;
        Plus(int r, int c, int s) : row(r), col(c), size(s), area(4*s + 1) {}
    };
    
    static int getMaxPlusSize(const vector<string>& grid, int row, int col) {
        int n = grid.size(), m = grid[0].size();
        int maxSize = 0;
        
        while (row - maxSize - 1 >= 0 && row + maxSize + 1 < n &&
               col - maxSize - 1 >= 0 && col + maxSize + 1 < m &&
               grid[row - maxSize - 1][col] == 'G' &&
               grid[row + maxSize + 1][col] == 'G' &&
               grid[row][col - maxSize - 1] == 'G' &&
               grid[row][col + maxSize + 1] == 'G') {
            maxSize++;
        }
        
        return maxSize;
    }
    
    static bool intersects(const Plus& p1, const Plus& p2) {
        vector<pair<int, int>> cells1, cells2;
        
        auto getCells = [](const Plus& p, vector<pair<int, int>>& cells) {
            cells.push_back({p.row, p.col});
            for (int i = 1; i <= p.size; i++) {
                cells.push_back({p.row - i, p.col});
                cells.push_back({p.row + i, p.col});
                cells.push_back({p.row, p.col - i});
                cells.push_back({p.row, p.col + i});
            }
        };
        
        getCells(p1, cells1);
        getCells(p2, cells2);
        
        sort(cells1.begin(), cells1.end());
        sort(cells2.begin(), cells2.end());
        
        int i = 0, j = 0;
        while (i < cells1.size() && j < cells2.size()) {
            if (cells1[i] == cells2[j]) return true;
            if (cells1[i] < cells2[j]) i++;
            else j++;
        }
        
        return false;
    }
    
public:
    static int solveTwoPluses(const vector<string>& grid) {
        vector<Plus> pluses;
        int n = grid.size(), m = grid[0].size();
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 'G') {
                    int maxSize = getMaxPlusSize(grid, i, j);
                    for (int size = 0; size <= maxSize; size++) {
                        pluses.emplace_back(i, j, size);
                    }
                }
            }
        }
        
        int maxProduct = 1;
        for (int i = 0; i < pluses.size(); i++) {
            for (int j = i + 1; j < pluses.size(); j++) {
                if (!intersects(pluses[i], pluses[j])) {
                    maxProduct = max(maxProduct, pluses[i].area * pluses[j].area);
                }
            }
        }
        
        return maxProduct;
    }
};

int twoPluses(vector<string> grid) {
    return OptimizedPlusSearchEngine::solveTwoPluses(grid);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int m = stoi(first_multiple_input[1]);

    vector<string> grid(n);

    for (int i = 0; i < n; i++) {
        string grid_item;
        getline(cin, grid_item);

        grid[i] = grid_item;
    }

    int result = twoPluses(grid);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
