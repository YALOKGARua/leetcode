#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

double calculateTime(int dx, int dy) {
    int diagonalMoves = min(abs(dx), abs(dy));
    int remainingX = abs(dx) - diagonalMoves;
    int remainingY = abs(dy) - diagonalMoves;
    
    return diagonalMoves * 0.5 + remainingX * 0.3 + remainingY * 0.4;
}

int main() {
    int x, y, u, v;
    cin >> x >> y >> u >> v;
    cin.ignore();
    
    vector<pair<int, int>> xOptions = {
        {u - x, 0},
        {u - x + 200, 0},
        {u - x - 200, 0}
    };
    
    vector<pair<int, int>> yOptions = {
        {0, v - y},
        {0, v - y + 150},
        {0, v - y - 150}
    };
    
    double minTime = 1e9;
    
    for (const auto& xOpt : xOptions) {
        for (const auto& yOpt : yOptions) {
            int dx = xOpt.first;
            int dy = yOpt.second;
            
            double time = calculateTime(dx, dy);
            minTime = min(minTime, time);
        }
    }
    
    cout << fixed << setprecision(1) << minTime << endl;
    
    return 0;
}
