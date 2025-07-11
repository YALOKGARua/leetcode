#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int size;
    cin >> size;
    cin.ignore();
    
    vector<string> map(size);
    for (int i = 0; i < size; i++) {
        getline(cin, map[i]);
    }
    
    int myId;
    cin >> myId;
    cin.ignore();
    
    while (true) {
        int entityCount;
        cin >> entityCount;
        cin.ignore();
        
        int myX = 0, myY = 0, myLife = 100;
        vector<pair<int, int> > mines;
        
        for (int i = 0; i < entityCount; i++) {
            string type;
            int id, x, y, life, gold;
            cin >> type >> id >> x >> y >> life >> gold;
            cin.ignore();
            
            if (type == "HERO" && id == myId) {
                myX = x;
                myY = y; 
                myLife = life;
            }
            if (type == "MINE" && id != myId) {
                mines.push_back(make_pair(x, y));
            }
        }
        
        string move = "WAIT";
        
        if (!mines.empty()) {
            int targetX = mines[0].first;
            int targetY = mines[0].second;
            int minDist = abs(myX - targetX) + abs(myY - targetY);
            
            for (int i = 1; i < mines.size(); i++) {
                int dist = abs(myX - mines[i].first) + abs(myY - mines[i].second);
                if (dist < minDist) {
                    minDist = dist;
                    targetX = mines[i].first;
                    targetY = mines[i].second;
                }
            }
            
            if (targetX > myX && myX + 1 < size && map[myY][myX + 1] != '#') {
                move = "EAST";
            } else if (targetX < myX && myX - 1 >= 0 && map[myY][myX - 1] != '#') {
                move = "WEST";  
            } else if (targetY > myY && myY + 1 < size && map[myY + 1][myX] != '#') {
                move = "SOUTH";
            } else if (targetY < myY && myY - 1 >= 0 && map[myY - 1][myX] != '#') {
                move = "NORTH";
            }
        }
        
        if (move == "WAIT") {
            if (myY - 1 >= 0 && map[myY - 1][myX] != '#') {
                move = "NORTH";
            } else if (myX + 1 < size && map[myY][myX + 1] != '#') {
                move = "EAST";
            } else if (myY + 1 < size && map[myY + 1][myX] != '#') {
                move = "SOUTH";
            } else if (myX - 1 >= 0 && map[myY][myX - 1] != '#') {
                move = "WEST";
            }
        }
        
        cout << move << endl;
    }
    
    return 0;
}