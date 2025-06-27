#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>

using namespace std;

struct Player {
    string name;
    int score;
    int originalIndex;
    
    Player(string n, int s, int idx) : name(n), score(s), originalIndex(idx) {}
};

bool compareResults(const Player& a, const Player& b) {
    if (a.score != b.score) {
        return a.score > b.score;
    }
    return a.originalIndex < b.originalIndex;
}

int calculateScore(int x, int y, int squareSize) {
    double halfSize = squareSize / 2.0;
    double radius = halfSize;
    double distanceFromCenter = sqrt(x * x + y * y);
    
    bool insideSquare = abs(x) <= halfSize && abs(y) <= halfSize;
    bool insideCircle = distanceFromCenter <= radius;
    bool insideDiamond = abs(x) + abs(y) <= halfSize;
    
    if (!insideSquare) {
        return 0;
    }
    
    if (insideDiamond) {
        return 15;
    } else if (insideCircle) {
        return 10;
    } else {
        return 5;
    }
}

int main() {
    int size;
    cin >> size;
    cin.ignore();
    
    int n;
    cin >> n;
    cin.ignore();
    
    vector<string> playerNames(n);
    map<string, int> playerScores;
    map<string, int> playerIndices;
    
    for (int i = 0; i < n; i++) {
        getline(cin, playerNames[i]);
        playerScores[playerNames[i]] = 0;
        playerIndices[playerNames[i]] = i;
    }
    
    int t;
    cin >> t;
    cin.ignore();
    
    for (int i = 0; i < t; i++) {
        string throwName;
        int throwX, throwY;
        cin >> throwName >> throwX >> throwY;
        cin.ignore();
        
        int points = calculateScore(throwX, throwY, size);
        playerScores[throwName] += points;
    }
    
    vector<Player> results;
    for (const string& name : playerNames) {
        results.emplace_back(name, playerScores[name], playerIndices[name]);
    }
    
    sort(results.begin(), results.end(), compareResults);
    
    for (const Player& player : results) {
        cout << player.name << " " << player.score << endl;
    }
    
    return 0;
}
