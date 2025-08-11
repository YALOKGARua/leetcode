#include <iostream>
#include <string>
#include <array>
#include <limits>
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <cmath>

using namespace std;

static inline uint64_t mix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    x ^= x >> 31;
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int first_init_input;
    if (!(cin >> first_init_input)) return 0;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int second_init_input;
    cin >> second_init_input; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int third_init_input;
    cin >> third_init_input; cin.ignore(numeric_limits<streamsize>::max(), '\n');

    uint64_t h = 1469598103934665603ULL;
    h ^= mix64(static_cast<uint64_t>(first_init_input));
    h ^= mix64(static_cast<uint64_t>(second_init_input));
    h ^= mix64(static_cast<uint64_t>(third_init_input));

    cerr << "init " << first_init_input << ' ' << second_init_input << ' ' << third_init_input << '\n' << flush;

    array<int, 5> usage = {0, 0, 0, 0, 0};
    long long turn = 0;
    string prev_state_key;
    int prev_action = -1;
    unordered_map<string, array<pair<double,int>,5>> state_stats;

    while (true) {
        string first_input, second_input, third_input, fourth_input;
        if (!getline(cin, first_input)) break;
        if (!getline(cin, second_input)) break;
        if (!getline(cin, third_input)) break;
        if (!getline(cin, fourth_input)) break;

        for (char ch : first_input) h ^= mix64(static_cast<unsigned char>(ch) + 1ull);
        for (char ch : second_input) h ^= mix64(static_cast<unsigned char>(ch) + 3ull);
        for (char ch : third_input) h ^= mix64(static_cast<unsigned char>(ch) + 5ull);
        for (char ch : fourth_input) h ^= mix64(static_cast<unsigned char>(ch) + 7ull);

        cerr << "turn " << turn << " chars " << first_input << ' ' << second_input << ' ' << third_input << ' ' << fourth_input << '\n' << flush;

        vector<pair<long long,long long>> pairs;
        pairs.reserve(static_cast<size_t>(third_init_input));
        for (int i = 0; i < third_init_input; i++) {
            long long fifth_input, sixth_input;
            cin >> fifth_input >> sixth_input;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (i < 5) cerr << "p " << i << ' ' << fifth_input << ' ' << sixth_input << '\n';
            h ^= mix64(static_cast<uint64_t>(fifth_input) * 1315423911ull);
            h ^= mix64(static_cast<uint64_t>(sixth_input) * 2654435761ull);
            pairs.emplace_back(fifth_input, sixth_input);
        }
        cerr << flush;

        if (prev_action != -1 && static_cast<int>(pairs.size()) == third_init_input && prev_action < third_init_input) {
            auto pr = pairs[prev_action];
            double reward = static_cast<double>(pr.first + pr.second);
            auto &arr = state_stats[prev_state_key];
            auto &st = arr[prev_action];
            st.first = (st.first * st.second + reward) / (st.second + 1);
            st.second += 1;
            cerr << "upd " << prev_state_key << ' ' << prev_action << ' ' << reward << ' ' << st.first << ' ' << st.second << '\n';
        }

        string state_key;
        state_key.reserve(8);
        state_key.push_back(!first_input.empty() ? first_input[0] : '?');
        state_key.push_back(!second_input.empty() ? second_input[0] : '?');
        state_key.push_back(!third_input.empty() ? third_input[0] : '?');
        state_key.push_back(!fourth_input.empty() ? fourth_input[0] : '?');

        int sharp = 0;
        for (char c : state_key) if (c == '#') sharp++;

        int k = static_cast<int>(pairs.size());
        if (k > 5) k = 5;
        auto get = [&](int i) { return pairs[i]; };
        long long W = first_init_input, H = second_init_input;
        long double bestScore = -1e300;
        int choice = 0;
        for (int i = 0; i < k; i++) {
            long long x = get(i).first;
            long long y = get(i).second;
            long long dL = x;
            long long dR = (W - 1) - x;
            long long dD = y;
            long long dU = (H - 1) - y;
            long double score = 0;
            score += (first_input.size() && first_input[0] == '#') ? dR : dL;
            score += (second_input.size() && second_input[0] == '#') ? dL : dR;
            score += (third_input.size() && third_input[0] == '#') ? dD : dU;
            score += (fourth_input.size() && fourth_input[0] == '#') ? dU : dD;
            score += 0.01L * (x + y);
            score -= 0.25L * usage[i];
            if (score > bestScore) { bestScore = score; choice = i; }
            cerr << "score " << i << ' ' << x << ' ' << y << ' ' << (double)score << '\n';
        }

        choice = max(0, min(choice, 4));

        char out = static_cast<char>('A' + choice);
        cout << out << '\n' << flush;
        cerr << "act " << state_key << ' ' << out << ' ' << choice << '\n' << flush;
        usage[choice]++;
        turn++;
        prev_state_key = state_key;
        prev_action = choice;
    }

    return 0;
}