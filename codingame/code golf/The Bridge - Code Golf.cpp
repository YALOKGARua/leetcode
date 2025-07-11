#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int m, v;
    cin >> m >> v;
    
    vector<string> road(4);
    for (int i = 0; i < 4; i++) {
        cin >> road[i];
    }
    
    while (true) {
        int s;
        cin >> s;
        
        vector<int> x(m), y(m), active(m);
        int aliveBikes = 0;
        
        for (int i = 0; i < m; i++) {
            cin >> x[i] >> y[i] >> active[i];
            if (active[i]) aliveBikes++;
        }
        
        if (aliveBikes < v) {
            cout << "WAIT" << endl;
            continue;
        }
        
        if (s == 0) {
            cout << "SPEED" << endl;
            continue;
        }
        
        bool canMoveUp = true, canMoveDown = true;
        bool hasImmediateDanger = false;
        int maxHoleChainAhead = 0;
        int maxHoleChainFar = 0;
        
        for (int i = 0; i < m; i++) {
            if (!active[i]) continue;
            
            if (y[i] == 0) canMoveUp = false;
            if (y[i] == 3) canMoveDown = false;
            
            for (int step = 1; step <= s; step++) {
                int checkX = x[i] + step;
                if (checkX < road[0].length() && road[y[i]][checkX] == '0') {
                    hasImmediateDanger = true;
                    break;
                }
            }
            
            int currentChain = 0;
            int maxChain = 0;
            for (int step = 1; step <= s + 5; step++) {
                int checkX = x[i] + step;
                if (checkX >= road[0].length()) break;
                
                if (road[y[i]][checkX] == '0') {
                    currentChain++;
                    maxChain = max(maxChain, currentChain);
                } else {
                    currentChain = 0;
                }
            }
            maxHoleChainAhead = max(maxHoleChainAhead, maxChain);
            
            currentChain = 0;
            maxChain = 0;
            for (int step = 1; step <= 15; step++) {
                int checkX = x[i] + step;
                if (checkX >= road[0].length()) break;
                
                if (road[y[i]][checkX] == '0') {
                    currentChain++;
                    maxChain = max(maxChain, currentChain);
                } else {
                    currentChain = 0;
                }
            }
            maxHoleChainFar = max(maxHoleChainFar, maxChain);
            
            if (canMoveUp && y[i] > 0) {
                for (int step = 1; step <= s; step++) {
                    int checkX = x[i] + step;
                    if (checkX < road[0].length()) {
                        if (road[y[i] - 1][checkX] == '0' || road[y[i]][checkX] == '0') {
                            canMoveUp = false;
                            break;
                        }
                    }
                }
            }
            
            if (canMoveDown && y[i] < 3) {
                for (int step = 1; step <= s; step++) {
                    int checkX = x[i] + step;
                    if (checkX < road[0].length()) {
                        if (road[y[i] + 1][checkX] == '0' || road[y[i]][checkX] == '0') {
                            canMoveDown = false;
                            break;
                        }
                    }
                }
            }
        }
        
        if (hasImmediateDanger) {
            if (s > maxHoleChainAhead) {
                cout << "JUMP" << endl;
            } else if (canMoveUp) {
                cout << "UP" << endl;
            } else if (canMoveDown) {
                cout << "DOWN" << endl;
            } else if (s < 10) {
                cout << "SPEED" << endl;
            } else {
                cout << "JUMP" << endl;
            }
            continue;
        }
        
        bool shouldMoveUp = false, shouldMoveDown = false;
        int bestLane = -1;
        int minDangerCount = 999;
        
        for (int i = 0; i < m; i++) {
            if (!active[i]) continue;
            
            vector<int> lanesDanger(4, 0);
            vector<int> lanesMaxChain(4, 0);
            
            for (int lane = 0; lane < 4; lane++) {
                int currentChain = 0;
                int maxChain = 0;
                
                for (int look = 1; look <= 15; look++) {
                    int checkX = x[i] + look;
                    if (checkX >= road[0].length()) break;
                    
                    if (road[lane][checkX] == '0') {
                        lanesDanger[lane]++;
                        currentChain++;
                        maxChain = max(maxChain, currentChain);
                    } else {
                        currentChain = 0;
                    }
                }
                lanesMaxChain[lane] = maxChain;
            }
            
            for (int lane = 0; lane < 4; lane++) {
                int score = lanesDanger[lane] * 10 + lanesMaxChain[lane];
                if (score < minDangerCount) {
                    minDangerCount = score;
                    bestLane = lane;
                }
            }
            
            if (bestLane != y[i]) {
                if (bestLane < y[i] && canMoveUp) {
                    shouldMoveUp = true;
                } else if (bestLane > y[i] && canMoveDown) {
                    shouldMoveDown = true;
                }
            }
        }
        
        if (maxHoleChainFar >= 7 && s < maxHoleChainFar + 1) {
            if (shouldMoveUp && canMoveUp) {
                cout << "UP" << endl;
            } else if (shouldMoveDown && canMoveDown) {
                cout << "DOWN" << endl;
            } else if (s < 10) {
                cout << "SPEED" << endl;
            } else {
                cout << "WAIT" << endl;
            }
        } else if (shouldMoveUp && canMoveUp) {
            cout << "UP" << endl;
        } else if (shouldMoveDown && canMoveDown) {
            cout << "DOWN" << endl;
        } else if (s < 6) {
            bool safeToAccelerate = true;
            for (int i = 0; i < m; i++) {
                if (!active[i]) continue;
                for (int step = 1; step <= s + 1; step++) {
                    int checkX = x[i] + step;
                    if (checkX < road[0].length() && road[y[i]][checkX] == '0') {
                        safeToAccelerate = false;
                        break;
                    }
                }
                if (!safeToAccelerate) break;
            }
            
            if (safeToAccelerate) {
                cout << "SPEED" << endl;
            } else {
                cout << "WAIT" << endl;
            }
        } else {
            cout << "WAIT" << endl;
        }
    }
    
    return 0;
}
