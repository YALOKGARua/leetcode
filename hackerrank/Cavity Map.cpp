#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

class CavityMapAnalyzer {
private:
    struct DirectionalOffsets {
        static constexpr int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    };
    
    static bool isValidCavityCandidate(const vector<string>& depthGrid, int centerRow, int centerCol) {
        int gridSize = depthGrid.size();
        
        if (centerRow <= 0 || centerRow >= gridSize - 1 || 
            centerCol <= 0 || centerCol >= gridSize - 1) {
            return false;
        }
        
        char centerDepth = depthGrid[centerRow][centerCol];
        
        for (int directionIndex = 0; directionIndex < 4; ++directionIndex) {
            int adjacentRow = centerRow + DirectionalOffsets::directions[directionIndex][0];
            int adjacentCol = centerCol + DirectionalOffsets::directions[directionIndex][1];
            
            char neighborDepth = depthGrid[adjacentRow][adjacentCol];
            
            if (neighborDepth >= centerDepth) {
                return false;
            }
        }
        
        return true;
    }
    
    static vector<pair<int, int>> identifyAllCavityPositions(const vector<string>& terrainMap) {
        vector<pair<int, int>> cavityCoordinates;
        int mapDimension = terrainMap.size();
        
        for (int rowIndex = 1; rowIndex < mapDimension - 1; ++rowIndex) {
            for (int colIndex = 1; colIndex < mapDimension - 1; ++colIndex) {
                if (isValidCavityCandidate(terrainMap, rowIndex, colIndex)) {
                    cavityCoordinates.emplace_back(rowIndex, colIndex);
                }
            }
        }
        
        return cavityCoordinates;
    }
    
public:
    static vector<string> processDepthMapForCavities(vector<string> inputGrid) {
        vector<string> processedGrid = inputGrid;
        auto detectedCavities = identifyAllCavityPositions(inputGrid);
        
        for (const auto& cavityPosition : detectedCavities) {
            int cavityRow = cavityPosition.first;
            int cavityColumn = cavityPosition.second;
            processedGrid[cavityRow][cavityColumn] = 'X';
        }
        
        return processedGrid;
    }
};

constexpr int CavityMapAnalyzer::DirectionalOffsets::directions[4][2];

vector<string> cavityMap(vector<string> grid) {
    return CavityMapAnalyzer::processDepthMapForCavities(grid);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<string> grid(n);

    for (int i = 0; i < n; i++) {
        string grid_item;
        getline(cin, grid_item);

        grid[i] = grid_item;
    }

    vector<string> result = cavityMap(grid);

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
