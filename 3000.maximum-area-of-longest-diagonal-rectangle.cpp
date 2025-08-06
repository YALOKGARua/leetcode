class Solution {
public:
    int areaOfMaxDiagonal(vector<vector<int>>& dimensions) {
        int maxDiagonal = 0;
        int maxArea = 0;
        for (auto& rect : dimensions) {
            int length = rect[0];
            int width = rect[1];
            int diagonal = length * length + width * width;
            int area = length * width;
            if (diagonal > maxDiagonal) {
                maxDiagonal = diagonal;
                maxArea = area;
            } else if (diagonal == maxDiagonal) {
                maxArea = max(maxArea, area);
            }
        }
        return maxArea;
    }
}; 