#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

int main() {
    int w, h, countX, countY;
    cin >> w >> h >> countX >> countY;
    cin.ignore();
    
    vector<int> xCoords;
    xCoords.push_back(0);
    xCoords.push_back(w);
    
    for (int i = 0; i < countX; i++) {
        int x;
        cin >> x;
        cin.ignore();
        xCoords.push_back(x);
    }
    
    vector<int> yCoords;
    yCoords.push_back(0);
    yCoords.push_back(h);
    
    for (int i = 0; i < countY; i++) {
        int y;
        cin >> y;
        cin.ignore();
        yCoords.push_back(y);
    }
    
    sort(xCoords.begin(), xCoords.end());
    sort(yCoords.begin(), yCoords.end());
    
    unordered_map<int, int> widthCount;
    for (int i = 0; i < xCoords.size(); i++) {
        for (int j = i + 1; j < xCoords.size(); j++) {
            int width = xCoords[j] - xCoords[i];
            widthCount[width]++;
        }
    }
    
    unordered_map<int, int> heightCount;
    for (int i = 0; i < yCoords.size(); i++) {
        for (int j = i + 1; j < yCoords.size(); j++) {
            int height = yCoords[j] - yCoords[i];
            heightCount[height]++;
        }
    }
    
    int squareCount = 0;
    for (const auto& widthPair : widthCount) {
        int size = widthPair.first;
        int widthFreq = widthPair.second;
        
        if (heightCount.count(size)) {
            int heightFreq = heightCount[size];
            squareCount += widthFreq * heightFreq;
        }
    }
    
    cout << squareCount << endl;
    
    return 0;
}
