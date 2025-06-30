#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

class LadybugHappinessAnalyzer {
private:
    static map<char, int> countLadybugsByColor(const string& boardConfiguration) {
        map<char, int> colorFrequencies;
        
        for (char boardCell : boardConfiguration) {
            if (boardCell != '_') {
                colorFrequencies[boardCell]++;
            }
        }
        
        return colorFrequencies;
    }
    
    static bool hasEmptyPositions(const string& gameBoard) {
        return gameBoard.find('_') != string::npos;
    }
    
    static bool validateCurrentHappinessState(const string& currentBoard) {
        int boardLength = currentBoard.length();
        
        for (int position = 0; position < boardLength; ++position) {
            char currentLadybug = currentBoard[position];
            
            if (currentLadybug == '_') continue;
            
            bool hasHappyNeighbor = false;
            
            if (position > 0 && currentBoard[position - 1] == currentLadybug) {
                hasHappyNeighbor = true;
            }
            
            if (position < boardLength - 1 && currentBoard[position + 1] == currentLadybug) {
                hasHappyNeighbor = true;
            }
            
            if (!hasHappyNeighbor) {
                return false;
            }
        }
        
        return true;
    }
    
    static bool canAllColorsBeHappy(const map<char, int>& ladybugColorCounts) {
        for (const auto& colorCountPair : ladybugColorCounts) {
            int colorQuantity = colorCountPair.second;
            
            if (colorQuantity == 1) {
                return false;
            }
        }
        
        return true;
    }
    
public:
    static string determineLadybugHappinessPossibility(const string& boardState) {
        if (boardState.empty()) {
            return "YES";
        }
        
        auto ladybugDistribution = countLadybugsByColor(boardState);
        
        if (ladybugDistribution.empty()) {
            return "YES";
        }
        
        bool canRearrange = hasEmptyPositions(boardState);
        
        if (!canRearrange) {
            return validateCurrentHappinessState(boardState) ? "YES" : "NO";
        }
        
        return canAllColorsBeHappy(ladybugDistribution) ? "YES" : "NO";
    }
};

class OptimizedLadybugSolver {
private:
    static bool isCurrentlyAllHappy(const string& board) {
        for (int i = 0; i < board.length(); i++) {
            if (board[i] == '_') continue;
            
            bool leftMatch = (i > 0) && (board[i-1] == board[i]);
            bool rightMatch = (i < board.length()-1) && (board[i+1] == board[i]);
            
            if (!leftMatch && !rightMatch) {
                return false;
            }
        }
        return true;
    }
    
public:
    static string solveLadybugHappiness(const string& b) {
        map<char, int> colorCount;
        bool hasEmpty = false;
        
        for (char c : b) {
            if (c == '_') {
                hasEmpty = true;
            } else {
                colorCount[c]++;
            }
        }
        
        if (colorCount.empty()) return "YES";
        
        if (!hasEmpty) {
            return isCurrentlyAllHappy(b) ? "YES" : "NO";
        }
        
        for (auto& pair : colorCount) {
            if (pair.second == 1) {
                return "NO";
            }
        }
        
        return "YES";
    }
};

string happyLadybugs(string b) {
    return OptimizedLadybugSolver::solveLadybugHappiness(b);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string g_temp;
    getline(cin, g_temp);

    int g = stoi(ltrim(rtrim(g_temp)));

    for (int g_itr = 0; g_itr < g; g_itr++) {
        string n_temp;
        getline(cin, n_temp);

        int n = stoi(ltrim(rtrim(n_temp)));

        string b;
        getline(cin, b);

        string result = happyLadybugs(b);

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
