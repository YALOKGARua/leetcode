#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

class BombermanGameSimulator {
private:
    static constexpr int EXPLOSION_DIRECTIONS[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    static vector<string> createFullBombGrid(int rows, int columns) {
        vector<string> fullGrid(rows, string(columns, 'O'));
        return fullGrid;
    }
    
    static vector<string> simulateExplosionPattern(const vector<string>& originalGrid, 
                                                  const vector<string>& bombPositions) {
        int gridHeight = originalGrid.size();
        int gridWidth = originalGrid[0].size();
        vector<string> postExplosionGrid = createFullBombGrid(gridHeight, gridWidth);
        
        for (int rowIndex = 0; rowIndex < gridHeight; ++rowIndex) {
            for (int columnIndex = 0; columnIndex < gridWidth; ++columnIndex) {
                if (bombPositions[rowIndex][columnIndex] == 'O') {
                    postExplosionGrid[rowIndex][columnIndex] = '.';
                    
                    for (int directionIndex = 0; directionIndex < 4; ++directionIndex) {
                        int adjacentRow = rowIndex + EXPLOSION_DIRECTIONS[directionIndex][0];
                        int adjacentColumn = columnIndex + EXPLOSION_DIRECTIONS[directionIndex][1];
                        
                        if (adjacentRow >= 0 && adjacentRow < gridHeight && 
                            adjacentColumn >= 0 && adjacentColumn < gridWidth) {
                            postExplosionGrid[adjacentRow][adjacentColumn] = '.';
                        }
                    }
                }
            }
        }
        
        return postExplosionGrid;
    }
    
    static vector<string> calculateCyclicGameState(int timeStamp, const vector<string>& initialConfiguration) {
        if (timeStamp == 1) {
            return initialConfiguration;
        }
        
        if (timeStamp % 2 == 0) {
            return createFullBombGrid(initialConfiguration.size(), initialConfiguration[0].size());
        }
        
        int cyclicPattern = ((timeStamp - 3) / 2) % 2;
        
        if (cyclicPattern == 0) {
            return simulateExplosionPattern(initialConfiguration, initialConfiguration);
        } else {
            vector<string> firstExplosionState = simulateExplosionPattern(initialConfiguration, initialConfiguration);
            return simulateExplosionPattern(initialConfiguration, firstExplosionState);
        }
    }
    
public:
    static vector<string> executeGameSimulation(int finalTime, const vector<string>& startingGrid) {
        return calculateCyclicGameState(finalTime, startingGrid);
    }
};

class OptimizedBombermanEngine {
private:
    static vector<string> generateAllBombsState(int rows, int cols) {
        return vector<string>(rows, string(cols, 'O'));
    }
    
    static vector<string> processExplosions(const vector<string>& grid, const vector<string>& explosionSources) {
        int rows = grid.size();
        int cols = grid[0].size();
        vector<string> result = generateAllBombsState(rows, cols);
        
        vector<vector<bool>> shouldExplode(rows, vector<bool>(cols, false));
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (explosionSources[i][j] == 'O') {
                    shouldExplode[i][j] = true;
                    
                    int dx[] = {-1, 1, 0, 0};
                    int dy[] = {0, 0, -1, 1};
                    
                    for (int k = 0; k < 4; k++) {
                        int nx = i + dx[k];
                        int ny = j + dy[k];
                        
                        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                            shouldExplode[nx][ny] = true;
                        }
                    }
                }
            }
        }
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (shouldExplode[i][j]) {
                    result[i][j] = '.';
                }
            }
        }
        
        return result;
    }
    
public:
    static vector<string> simulateBombermanGame(int n, const vector<string>& grid) {
        if (n == 1) {
            return grid;
        }
        
        if (n % 2 == 0) {
            return generateAllBombsState(grid.size(), grid[0].size());
        }
        
        if ((n - 3) % 4 == 0) {
            return processExplosions(grid, grid);
        } else {
            vector<string> state3 = processExplosions(grid, grid);
            return processExplosions(grid, state3);
        }
    }
};

constexpr int BombermanGameSimulator::EXPLOSION_DIRECTIONS[4][2];

vector<string> bomberMan(int n, vector<string> grid) {
    return OptimizedBombermanEngine::simulateBombermanGame(n, grid);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int r = stoi(first_multiple_input[0]);

    int c = stoi(first_multiple_input[1]);

    int n = stoi(first_multiple_input[2]);

    vector<string> grid(r);

    for (int i = 0; i < r; i++) {
        string grid_item;
        getline(cin, grid_item);

        grid[i] = grid_item;
    }

    vector<string> result = bomberMan(n, grid);

    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

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
