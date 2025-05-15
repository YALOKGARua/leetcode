#include <ctype.h>
#include <stdbool.h>
#include <string.h>

bool isValid(char* word) {
    int n = strlen(word);
    if (n < 3) return false;
    int vowel = 0, consonant = 0;
    for (int i = 0; i < n; i++) {
        char c = word[i];
        if (isdigit(c)) continue;
        if (isalpha(c)) {
            char lower = tolower(c);
            if (lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u')
                vowel = 1;
            else
                consonant = 1;
        } else {
            return false;
        }
    }
    return vowel && consonant;
} 