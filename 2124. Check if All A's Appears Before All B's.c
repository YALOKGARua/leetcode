#include <stdbool.h>

bool checkString(char* s) {
    bool seen_b = false;
    
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == 'b') {
            seen_b = true;
        } else if (seen_b) {
            return false;
        }
    }
    
    return true;
} 