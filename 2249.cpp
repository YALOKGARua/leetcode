#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int countLatticePoints(vector<vector<int>>& circles) {
        int count = 0;
        for (int x = 0; x <= 200; x++) {
            for (int y = 0; y <= 200; y++) {
                for (const auto& circle : circles) {
                    int dx = x - circle[0];
                    int dy = y - circle[1];
                    int r = circle[2];
                    if (dx * dx + dy * dy <= r * r) {
                        count++;
                        break;
                    }
                }
            }
        }
        return count;
    }
}; 