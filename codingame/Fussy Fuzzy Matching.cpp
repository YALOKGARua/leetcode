#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

bool isLetter(char c) { return isalpha(c); }
bool isDigit(char c) { return isdigit(c); }
bool isOther(char c) { return !isLetter(c) && !isDigit(c); }

int letterDistance(char a, char b) {
    char a_lower = tolower(a);
    char b_lower = tolower(b);
    return abs(a_lower - b_lower);
}

int numberDistance(const string& num1, const string& num2) {
    return abs(stoi(num1) - stoi(num2));
}

bool matches(const string& template_str, const string& candidate, 
             bool letterCase, int letterFuzz, int numberFuzz, bool otherFuzz) {
    int i = 0, j = 0;
    while (i < template_str.length() && j < candidate.length()) {
        char t = template_str[i];
        char c = candidate[j];
        if (isLetter(t) && isLetter(c)) {
            if (letterCase && t != c) return false;
            if (letterDistance(t, c) > letterFuzz) return false;
            i++; j++;
        }
        else if (isDigit(t) && isDigit(c)) {
            string num1, num2;
            while (i < template_str.length() && isDigit(template_str[i])) num1 += template_str[i++];
            while (j < candidate.length() && isDigit(candidate[j])) num2 += candidate[j++];
            if (numberDistance(num1, num2) > numberFuzz) return false;
        }
        else if (isOther(t) && isOther(c)) {
            if (otherFuzz) {
                if (t != c) return false;
            }
            i++; j++;
        }
        else if (!isLetter(t) && !isLetter(c)) {
            // both are not letters, treat as 'other' for otherFuzz=false
            i++; j++;
        }
        else {
            return false;
        }
    }
    return i == template_str.length() && j == candidate.length();
}

int main() {
    string letter_case;
    getline(cin, letter_case);
    int letter_fuzz;
    cin >> letter_fuzz; cin.ignore();
    int number_fuzz;
    cin >> number_fuzz; cin.ignore();
    string other_fuzz;
    getline(cin, other_fuzz);
    string _template;
    getline(cin, _template);
    int n;
    cin >> n; cin.ignore();
    vector<string> candidates(n);
    for (int i = 0; i < n; i++) getline(cin, candidates[i]);
    for (int i = 0; i < n; i++) {
        bool result = matches(_template, candidates[i], 
                            letter_case == "true", letter_fuzz, 
                            number_fuzz, other_fuzz == "true");
        cout << (result ? "true" : "false") << endl;
    }
    return 0;
}
