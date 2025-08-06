class Solution {
public:
    bool findRotation(vector<vector<int>>& mat, vector<vector<int>>& target) {
        int n = mat.size();
        for (int k = 0; k < 4; ++k) {
            bool match = true;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    int rotated_i, rotated_j;
                    if (k == 0) {
                        rotated_i = i;
                        rotated_j = j;
                    } else if (k == 1) {
                        rotated_i = j;
                        rotated_j = n - 1 - i;
                    } else if (k == 2) {
                        rotated_i = n - 1 - i;
                        rotated_j = n - 1 - j;
                    } else {
                        rotated_i = n - 1 - j;
                        rotated_j = i;
                    }
                    if (mat[rotated_i][rotated_j] != target[i][j]) {
                        match = false;
                        break;
                    }
                }
                if (!match) break;
            }
            if (match) return true;
        }
        return false;
    }
}; 