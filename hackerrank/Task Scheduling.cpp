#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

struct Task {
    int duration{};
    int deadline{};
    
    constexpr Task(int d, int dl) noexcept : duration{d}, deadline{dl} {}
    
    constexpr bool operator<(const Task& other) const noexcept {
        if (duration != other.duration) return duration < other.duration;
        return deadline < other.deadline;
    }
    
    [[nodiscard]] constexpr bool is_valid() const noexcept {
        return duration > 0 && deadline > 0;
    }
};

constexpr int calculate_overshoot(int completion_time, const Task& task) noexcept {
    return max(0, completion_time - task.deadline);
}

int calculateMaxOvershoot(vector<Task> tasks) {
    if (tasks.empty()) return 0;
    
    vector<int> remaining;
    remaining.reserve(tasks.size());
    
    for (const auto& task : tasks) {
        remaining.push_back(task.duration);
    }
    
    int current_time = 0;
    int max_overshoot = 0;
    
    while (true) {
        int next_task = -1;
        int earliest_deadline = INT_MAX;
        
        for (size_t i = 0; i < tasks.size(); ++i) {
            if (remaining[i] > 0 && tasks[i].deadline < earliest_deadline) {
                earliest_deadline = tasks[i].deadline;
                next_task = static_cast<int>(i);
            }
        }
        
        if (next_task == -1) break;
        
        ++current_time;
        --remaining[next_task];
        
        if (remaining[next_task] == 0) {
            int overshoot = calculate_overshoot(current_time, tasks[next_task]);
            max_overshoot = max(max_overshoot, overshoot);
        }
    }
    
    return max_overshoot;
}

[[maybe_unused]] constexpr int taskScheduling(int d, int m) noexcept {
    return max(0, d - m);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));
    
    vector<Task> all_tasks;
    all_tasks.reserve(static_cast<size_t>(t));

    for (int t_itr = 0; t_itr < t; ++t_itr) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        auto first_multiple_input = split(rtrim(first_multiple_input_temp));

        int d = stoi(first_multiple_input[0]);
        int m = stoi(first_multiple_input[1]);
        
        all_tasks.emplace_back(d, m);
        
        int result = calculateMaxOvershoot(all_tasks);
        fout << result << "\n";
    }

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
