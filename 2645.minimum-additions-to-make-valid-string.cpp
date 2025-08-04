class Solution {
public:
    int addMinimum(string word) {
        int n = word.length();
        int insertions = 0;
        int expected = 0;
        
        for (int i = 0; i < n; i++) {
            char current = word[i];
            
            if (current == 'a') {
                if (expected != 0) {
                    insertions += expected;
                }
                expected = 1;
            } else if (current == 'b') {
                if (expected == 0) {
                    insertions += 1;
                } else if (expected == 2) {
                    insertions += 1;
                }
                expected = 2;
            } else if (current == 'c') {
                if (expected == 0) {
                    insertions += 2;
                } else if (expected == 1) {
                    insertions += 1;
                }
                expected = 0;
            }
        }
        
        if (expected == 1) {
            insertions += 2;
        } else if (expected == 2) {
            insertions += 1;
        }
        
        return insertions;
    }
}; 