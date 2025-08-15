#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

static inline bool ff_is_letter(char c) {
    return isalpha(static_cast<unsigned char>(c));
}

static inline bool ff_is_digit(char c) {
    return isdigit(static_cast<unsigned char>(c));
}

static inline bool ff_is_alnum(char c) {
    return isalnum(static_cast<unsigned char>(c));
}

static inline long long ff_read_number(const string& s, size_t& i) {
    long long v = 0;
    while (i < s.size() && ff_is_digit(s[i])) {
        v = v * 10 + (s[i] - '0');
        ++i;
    }
    return v;
}

static inline bool ff_match_letter(char a, char b, bool letterCase, int letterFuzz) {
    if (letterCase) {
        bool aLower = islower(static_cast<unsigned char>(a));
        bool bLower = islower(static_cast<unsigned char>(b));
        if (aLower != bLower) return false;
    }
    int da = tolower(static_cast<unsigned char>(a));
    int db = tolower(static_cast<unsigned char>(b));
    return abs(da - db) <= letterFuzz;
}

static bool ff_matches(const string& t, const string& c, bool letterCase, int letterFuzz, int numberFuzz, bool otherFuzz) {
    size_t i = 0, j = 0;
    while (i < t.size() && j < c.size()) {
        char a = t[i];
        char b = c[j];

        if (ff_is_digit(a) && ff_is_digit(b)) {
            size_t ii = i, jj = j;
            long long va = ff_read_number(t, ii);
            long long vb = ff_read_number(c, jj);
            long long diff = va - vb;
            if (diff < 0) diff = -diff;
            if (diff > numberFuzz) return false;
            i = ii;
            j = jj;
            continue;
        }

        if (ff_is_letter(a) && ff_is_letter(b)) {
            if (!ff_match_letter(a, b, letterCase, letterFuzz)) return false;
            ++i;
            ++j;
            continue;
        }

        bool aAn = ff_is_alnum(a);
        bool bAn = ff_is_alnum(b);
        if (!aAn && !bAn) {
            if (otherFuzz) {
                if (a != b) return false;
            }
            ++i;
            ++j;
            continue;
        }

        return false;
    }
    return i == t.size() && j == c.size();
}

int main() {
    string letter_case;
    if (!getline(cin, letter_case)) return 0;
    int letter_fuzz;
    cin >> letter_fuzz; cin.ignore();
    int number_fuzz;
    cin >> number_fuzz; cin.ignore();
    string other_fuzz;
    getline(cin, other_fuzz);
    string tmpl;
    getline(cin, tmpl);
    int n;
    cin >> n; cin.ignore();
    vector<string> candidates(n);
    for (int i = 0; i < n; ++i) getline(cin, candidates[i]);

    bool letterCase = (letter_case == "true");
    bool otherFuzz = (other_fuzz == "true");

    for (int i = 0; i < n; ++i) {
        bool ok = ff_matches(tmpl, candidates[i], letterCase, letter_fuzz, number_fuzz, otherFuzz);
        cout << (ok ? "true" : "false") << endl;
    }
    return 0;
}