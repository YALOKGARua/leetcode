#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

struct Circle {
    int centerX, centerY;
    int diameter;
    string operation;
    
    Circle(int x, int y, int d, string op) : centerX(x), centerY(y), diameter(d), operation(op) {}
};

vector<Circle> parseInstructions(const string& instructions) {
    vector<Circle> circles;
    istringstream iss(instructions);
    string token;
    
    while (iss >> token) {
        string operation = "MOW";
        string coords = token;
        
        if (token.substr(0, 8) == "PLANTMOW") {
            operation = "PLANTMOW";
            coords = token.substr(8);
        } else if (token.substr(0, 5) == "PLANT") {
            operation = "PLANT";
            coords = token.substr(5);
        }
        
        int x = coords[0] - 'a';
        int y = coords[1] - 'a';
        int diameter = stoi(coords.substr(2));
        
        circles.emplace_back(x, y, diameter, operation);
    }
    
    return circles;
}

bool isInsideCircle(int x, int y, int centerX, int centerY, int diameter) {
    double radius = diameter / 2.0;
    double distance = sqrt((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY));
    return distance <= radius;
}

int main() {
    string instructions;
    getline(cin, instructions);
    
    const int WIDTH = 19;
    const int HEIGHT = 25;
    const char CROP = 'X';
    const char MOWED = ' ';
    
    vector<vector<char>> field(HEIGHT, vector<char>(WIDTH, CROP));
    
    vector<Circle> circles = parseInstructions(instructions);
    
    for (const Circle& circle : circles) {
        for (int row = 0; row < HEIGHT; row++) {
            for (int col = 0; col < WIDTH; col++) {
                if (isInsideCircle(col, row, circle.centerX, circle.centerY, circle.diameter)) {
                    if (circle.operation == "MOW") {
                        field[row][col] = MOWED;
                    } else if (circle.operation == "PLANT") {
                        field[row][col] = CROP;
                    } else if (circle.operation == "PLANTMOW") {
                        field[row][col] = (field[row][col] == CROP) ? MOWED : CROP;
                    }
                }
            }
        }
    }
    
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            if (field[row][col] == CROP) {
                cout << "{}";
            } else {
                cout << "  ";
            }
        }
        cout << endl;
    }
    
    return 0;
}
