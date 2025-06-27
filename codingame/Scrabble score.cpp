#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

struct Position {
    int row, col;
    Position(int r, int c) : row(r), col(c) {}
};

class ScrabbleScorer {
private:
    map<char, int> tileScores;
    vector<string> specialBoard;
    vector<string> previousBoard;
    vector<string> currentBoard;
    vector<Position> newTiles;
    int width, height;
    
public:
    void parseTiles(int nbTiles) {
        for (int i = 0; i < nbTiles; i++) {
            string character;
            int score;
            cin >> character >> score;
            cin.ignore();
            tileScores[character[0]] = score;
        }
    }
    
    void parseBoards(int w, int h) {
        width = w;
        height = h;
        
        specialBoard.resize(height);
        previousBoard.resize(height);
        currentBoard.resize(height);
        
        for (int i = 0; i < height; i++) {
            getline(cin, specialBoard[i]);
        }
        
        for (int i = 0; i < height; i++) {
            getline(cin, previousBoard[i]);
        }
        
        for (int i = 0; i < height; i++) {
            getline(cin, currentBoard[i]);
        }
        
        findNewTiles();
    }
    
    void findNewTiles() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (previousBoard[i][j] != currentBoard[i][j]) {
                    newTiles.push_back(Position(i, j));
                }
            }
        }
    }
    
    bool isNewTile(int row, int col) {
        for (const Position& pos : newTiles) {
            if (pos.row == row && pos.col == col) {
                return true;
            }
        }
        return false;
    }
    
    string getHorizontalWord(int row, int col) {
        int start = col;
        while (start > 0 && currentBoard[row][start - 1] != '.') {
            start--;
        }
        
        int end = col;
        while (end < width - 1 && currentBoard[row][end + 1] != '.') {
            end++;
        }
        
        if (start == end) return "";
        
        string word = "";
        for (int j = start; j <= end; j++) {
            word += currentBoard[row][j];
        }
        return word;
    }
    
    string getVerticalWord(int row, int col) {
        int start = row;
        while (start > 0 && currentBoard[start - 1][col] != '.') {
            start--;
        }
        
        int end = row;
        while (end < height - 1 && currentBoard[end + 1][col] != '.') {
            end++;
        }
        
        if (start == end) return "";
        
        string word = "";
        for (int i = start; i <= end; i++) {
            word += currentBoard[i][col];
        }
        return word;
    }
    
    int calculateWordScore(const string& word, int startRow, int startCol, bool horizontal) {
        int baseScore = 0;
        int wordMultiplier = 1;
        
        for (int i = 0; i < word.length(); i++) {
            int row = horizontal ? startRow : startRow + i;
            int col = horizontal ? startCol + i : startCol;
            
            char tile = word[i];
            int tileScore = tileScores[tile];
            
            if (isNewTile(row, col)) {
                char special = specialBoard[row][col];
                if (special == 'l') {
                    tileScore *= 2;
                } else if (special == 'L') {
                    tileScore *= 3;
                } else if (special == 'w') {
                    wordMultiplier *= 2;
                } else if (special == 'W') {
                    wordMultiplier *= 3;
                }
            }
            
            baseScore += tileScore;
        }
        
        return baseScore * wordMultiplier;
    }
    
    void calculateScore() {
        set<string> processedWords;
        vector<pair<string, int>> wordsWithScores;
        int totalScore = 0;
        
        for (const Position& pos : newTiles) {
            string hWord = getHorizontalWord(pos.row, pos.col);
            if (!hWord.empty() && processedWords.find(hWord) == processedWords.end()) {
                int start = pos.col;
                while (start > 0 && currentBoard[pos.row][start - 1] != '.') {
                    start--;
                }
                int score = calculateWordScore(hWord, pos.row, start, true);
                wordsWithScores.push_back({hWord, score});
                processedWords.insert(hWord);
                totalScore += score;
            }
            
            string vWord = getVerticalWord(pos.row, pos.col);
            if (!vWord.empty() && processedWords.find(vWord) == processedWords.end()) {
                int start = pos.row;
                while (start > 0 && currentBoard[start - 1][pos.col] != '.') {
                    start--;
                }
                int score = calculateWordScore(vWord, start, pos.col, false);
                wordsWithScores.push_back({vWord, score});
                processedWords.insert(vWord);
                totalScore += score;
            }
        }
        
        sort(wordsWithScores.begin(), wordsWithScores.end());
        
        for (const auto& wordScore : wordsWithScores) {
            cout << wordScore.first << " " << wordScore.second << endl;
        }
        
        if (newTiles.size() == 7) {
            cout << "Bonus 50" << endl;
            totalScore += 50;
        }
        
        cout << "Total " << totalScore << endl;
    }
};

int main() {
    ScrabbleScorer scorer;
    
    int nbTiles;
    cin >> nbTiles;
    cin.ignore();
    scorer.parseTiles(nbTiles);
    
    int width, height;
    cin >> width >> height;
    cin.ignore();
    scorer.parseBoards(width, height);
    
    scorer.calculateScore();
    
    return 0;
}
