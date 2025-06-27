#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Rectangle {
    int r, c, width, height;
    
    Rectangle(int row, int col, int w, int h) : r(row), c(col), width(w), height(h) {}
    
    bool operator<(const Rectangle& other) const {
        if (r != other.r) return r < other.r;
        if (c != other.c) return c < other.c;
        return width < other.width;
    }
};

bool isValidRectangle(const vector<vector<int>>& grid, int targetRow, int targetCol, 
                     int rectR, int rectC, int width, int height, int targetValue) {
    int w = grid[0].size();
    int h = grid.size();
    
    if (rectR + height > h || rectC + width > w) {
        return false;
    }
    
    bool coversTarget = (targetRow >= rectR && targetRow < rectR + height && 
                        targetCol >= rectC && targetCol < rectC + width);
    if (!coversTarget) {
        return false;
    }
    
    for (int i = rectR; i < rectR + height; i++) {
        for (int j = rectC; j < rectC + width; j++) {
            if (grid[i][j] > 0 && (i != targetRow || j != targetCol)) {
                return false;
            }
        }
    }
    
    return true;
}

vector<Rectangle> findGoodRectangles(const vector<vector<int>>& grid, 
                                   int targetRow, int targetCol, int targetValue) {
    vector<Rectangle> goodRectangles;
    int w = grid[0].size();
    int h = grid.size();
    
    for (int width = 1; width <= w; width++) {
        if (targetValue % width == 0) {
            int height = targetValue / width;
            if (height <= h) {
                for (int r = 0; r <= h - height; r++) {
                    for (int c = 0; c <= w - width; c++) {
                        if (isValidRectangle(grid, targetRow, targetCol, r, c, width, height, targetValue)) {
                            goodRectangles.push_back(Rectangle(r, c, width, height));
                        }
                    }
                }
            }
        }
    }
    
    sort(goodRectangles.begin(), goodRectangles.end());
    return goodRectangles;
}

int main() {
    int w, h;
    cin >> w >> h;
    cin.ignore();
    
    vector<vector<int>> grid(h, vector<int>(w));
    
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> grid[i][j];
            cin.ignore();
        }
    }
    
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (grid[i][j] > 0) {
                vector<Rectangle> goodRectangles = findGoodRectangles(grid, i, j, grid[i][j]);
                
                if (!goodRectangles.empty()) {
                    cout << i << " " << j << " " << grid[i][j] << endl;
                    
                    for (const Rectangle& rect : goodRectangles) {
                        cout << rect.r << " " << rect.c << " " 
                             << rect.width << " " << rect.height << endl;
                    }
                }
            }
        }
    }
    
    return 0;
}
