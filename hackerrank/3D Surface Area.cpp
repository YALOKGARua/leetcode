#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

class ThreeDimensionalSurfaceCalculator {
private:
    static constexpr int DIRECTIONAL_OFFSETS[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    static int calculateTopBottomSurfaceArea(const vector<vector<int>>& heightMatrix) {
        int topBottomArea = 0;
        
        for (const auto& row : heightMatrix) {
            for (int cellHeight : row) {
                if (cellHeight > 0) {
                    topBottomArea += 2;
                }
            }
        }
        
        return topBottomArea;
    }
    
    static int calculateSideSurfaceArea(const vector<vector<int>>& heightGrid) {
        int gridRows = heightGrid.size();
        int gridColumns = heightGrid[0].size();
        int lateralSurfaceArea = 0;
        
        for (int rowIndex = 0; rowIndex < gridRows; ++rowIndex) {
            for (int columnIndex = 0; columnIndex < gridColumns; ++columnIndex) {
                int currentCellHeight = heightGrid[rowIndex][columnIndex];
                
                if (currentCellHeight == 0) continue;
                
                for (int directionIndex = 0; directionIndex < 4; ++directionIndex) {
                    int adjacentRow = rowIndex + DIRECTIONAL_OFFSETS[directionIndex][0];
                    int adjacentColumn = columnIndex + DIRECTIONAL_OFFSETS[directionIndex][1];
                    
                    int neighborHeight = 0;
                    if (adjacentRow >= 0 && adjacentRow < gridRows && 
                        adjacentColumn >= 0 && adjacentColumn < gridColumns) {
                        neighborHeight = heightGrid[adjacentRow][adjacentColumn];
                    }
                    
                    if (currentCellHeight > neighborHeight) {
                        lateralSurfaceArea += (currentCellHeight - neighborHeight);
                    }
                }
            }
        }
        
        return lateralSurfaceArea;
    }
    
public:
    static int computeTotalSurfaceArea(const vector<vector<int>>& cubeHeightMatrix) {
        int horizontalSurfaceArea = calculateTopBottomSurfaceArea(cubeHeightMatrix);
        int verticalSurfaceArea = calculateSideSurfaceArea(cubeHeightMatrix);
        
        return horizontalSurfaceArea + verticalSurfaceArea;
    }
};

class OptimizedSurfaceAreaCalculator {
private:
    static bool isValidPosition(int row, int col, int maxRows, int maxCols) {
        return row >= 0 && row < maxRows && col >= 0 && col < maxCols;
    }
    
    static int getHeightAtPosition(const vector<vector<int>>& grid, int row, int col) {
        if (!isValidPosition(row, col, grid.size(), grid[0].size())) {
            return 0;
        }
        return grid[row][col];
    }
    
public:
    static int calculateSurfaceAreaOptimized(const vector<vector<int>>& A) {
        int totalSurfaceArea = 0;
        int rows = A.size();
        int cols = A[0].size();
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                int currentHeight = A[i][j];
                
                if (currentHeight > 0) {
                    totalSurfaceArea += 2;
                    
                    totalSurfaceArea += max(0, currentHeight - getHeightAtPosition(A, i-1, j));
                    totalSurfaceArea += max(0, currentHeight - getHeightAtPosition(A, i+1, j));
                    totalSurfaceArea += max(0, currentHeight - getHeightAtPosition(A, i, j-1));
                    totalSurfaceArea += max(0, currentHeight - getHeightAtPosition(A, i, j+1));
                }
            }
        }
        
        return totalSurfaceArea;
    }
};

constexpr int ThreeDimensionalSurfaceCalculator::DIRECTIONAL_OFFSETS[4][2];

int surfaceArea(vector<vector<int>> A) {
    return OptimizedSurfaceAreaCalculator::calculateSurfaceAreaOptimized(A);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int H = stoi(first_multiple_input[0]);

    int W = stoi(first_multiple_input[1]);

    vector<vector<int>> A(H);

    for (int i = 0; i < H; i++) {
        A[i].resize(W);

        string A_row_temp_temp;
        getline(cin, A_row_temp_temp);

        vector<string> A_row_temp = split(rtrim(A_row_temp_temp));

        for (int j = 0; j < W; j++) {
            int A_row_item = stoi(A_row_temp[j]);

            A[i][j] = A_row_item;
        }
    }

    int result = surfaceArea(A);

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
