#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

class TwoDimensionalPatternMatcher {
private:
    static bool validatePatternAtPosition(const vector<string>& mainGrid, const vector<string>& searchPattern, 
                                        int startRow, int startColumn) {
        int patternHeight = searchPattern.size();
        int patternWidth = searchPattern[0].size();
        
        for (int patternRowIndex = 0; patternRowIndex < patternHeight; ++patternRowIndex) {
            for (int patternColIndex = 0; patternColIndex < patternWidth; ++patternColIndex) {
                int gridRowPosition = startRow + patternRowIndex;
                int gridColPosition = startColumn + patternColIndex;
                
                if (mainGrid[gridRowPosition][gridColPosition] != searchPattern[patternRowIndex][patternColIndex]) {
                    return false;
                }
            }
        }
        
        return true;
    }
    
    static bool isPatternPositionValid(int gridHeight, int gridWidth, int patternHeight, int patternWidth,
                                     int candidateRow, int candidateColumn) {
        return (candidateRow + patternHeight <= gridHeight) && 
               (candidateColumn + patternWidth <= gridWidth);
    }
    
    static bool performOptimizedPatternSearch(const vector<string>& targetGrid, const vector<string>& targetPattern) {
        int gridRows = targetGrid.size();
        int gridColumns = targetGrid[0].size();
        int patternRows = targetPattern.size();
        int patternColumns = targetPattern[0].size();
        
        for (int currentRow = 0; currentRow <= gridRows - patternRows; ++currentRow) {
            for (int currentColumn = 0; currentColumn <= gridColumns - patternColumns; ++currentColumn) {
                if (validatePatternAtPosition(targetGrid, targetPattern, currentRow, currentColumn)) {
                    return true;
                }
            }
        }
        
        return false;
    }
    
public:
    static string executeGridPatternSearch(const vector<string>& gridData, const vector<string>& patternData) {
        if (patternData.empty() || gridData.empty()) {
            return "NO";
        }
        
        bool patternFound = performOptimizedPatternSearch(gridData, patternData);
        return patternFound ? "YES" : "NO";
    }
};

class StringMatchingOptimizer {
private:
    static bool checkSubmatrixMatch(const vector<string>& grid, const vector<string>& pattern, int row, int col) {
        int patternH = pattern.size();
        int patternW = pattern[0].length();
        
        for (int i = 0; i < patternH; i++) {
            const string& gridRow = grid[row + i];
            const string& patternRow = pattern[i];
            
            if (gridRow.substr(col, patternW) != patternRow) {
                return false;
            }
        }
        
        return true;
    }
    
public:
    static string findPatternInGrid(const vector<string>& G, const vector<string>& P) {
        int gridRows = G.size();
        int gridCols = G[0].length();
        int patternRows = P.size();
        int patternCols = P[0].length();
        
        for (int startRow = 0; startRow <= gridRows - patternRows; startRow++) {
            for (int startCol = 0; startCol <= gridCols - patternCols; startCol++) {
                if (checkSubmatrixMatch(G, P, startRow, startCol)) {
                    return "YES";
                }
            }
        }
        
        return "NO";
    }
};

string gridSearch(vector<string> G, vector<string> P) {
    return StringMatchingOptimizer::findPatternInGrid(G, P);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int R = stoi(first_multiple_input[0]);

        int C = stoi(first_multiple_input[1]);

        vector<string> G(R);

        for (int i = 0; i < R; i++) {
            string G_item;
            getline(cin, G_item);

            G[i] = G_item;
        }

        string second_multiple_input_temp;
        getline(cin, second_multiple_input_temp);

        vector<string> second_multiple_input = split(rtrim(second_multiple_input_temp));

        int r = stoi(second_multiple_input[0]);

        int c = stoi(second_multiple_input[1]);

        vector<string> P(r);

        for (int i = 0; i < r; i++) {
            string P_item;
            getline(cin, P_item);

            P[i] = P_item;
        }

        string result = gridSearch(G, P);

        fout << result << "\n";
    }

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
