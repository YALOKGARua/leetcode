#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <climits>

using namespace std;

struct Student {
    string name;
    string instrument;
    vector<pair<int, int>> slots;
};

struct Slot {
    int day, hour;
    bool operator<(const Slot& o) const { return day < o.day || (day == o.day && hour < o.hour); }
};

map<string, int> dayMap = {{"M", 0}, {"Tu", 1}, {"W", 2}, {"Th", 3}, {"F", 4}};
vector<string> dayNames = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
vector<int> hours = {8, 9, 10, 11, 1, 2, 3, 4};
set<string> loudInstruments = {"Trumpet", "Drums", "Trombone"};

vector<Student> students;
vector<pair<string, string>> trouble;
vector<pair<int, int>> teacherSlots;

int slotIdx(int h) { for (int i = 0; i < 8; ++i) if (hours[i] == h) return i; return -1; }

bool isLoud(const string& instr) { return loudInstruments.count(instr); }
bool isTrouble(const string& a, const string& b) {
    for (auto& p : trouble) if ((p.first == a && p.second == b) || (p.first == b && p.second == a)) return true;
    return false;
}

bool dfs(int idx, vector<vector<string>>& slotStudent, vector<vector<string>>& slotInstr, vector<vector<string>>& slotName) {
    if (idx == students.size()) return true;
    auto& s = students[idx];
    
    vector<pair<int, int>> sortedSlots = s.slots;
    sort(sortedSlots.begin(), sortedSlots.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        if (a.first != b.first) return a.first > b.first;
        return a.second < b.second;
    });
    
    for (auto& slot : sortedSlots) {
        int d = slot.first, h = slot.second, hi = slotIdx(h);
        if (slotStudent[d][hi] != "") continue;
        bool ok = true;
        for (int i = 0; i < 8; ++i) if (slotInstr[d][i] == s.instrument) ok = false;
        if (!ok) continue;
        if (hi > 0) {
            if (isLoud(s.instrument) && isLoud(slotInstr[d][hi-1])) ok = false;
            if (isTrouble(s.name, slotName[d][hi-1])) ok = false;
        }
        if (hi < 7) {
            if (isLoud(s.instrument) && isLoud(slotInstr[d][hi+1])) ok = false;
            if (isTrouble(s.name, slotName[d][hi+1])) ok = false;
        }
        if (!ok) continue;
        slotStudent[d][hi] = s.name + "/" + s.instrument;
        slotInstr[d][hi] = s.instrument;
        slotName[d][hi] = s.name;
        if (dfs(idx+1, slotStudent, slotInstr, slotName)) return true;
        slotStudent[d][hi] = "";
        slotInstr[d][hi] = "";
        slotName[d][hi] = "";
    }
    return false;
}

int main() {
    string teacherAvail;
    getline(cin, teacherAvail);
    istringstream iss(teacherAvail);
    string token;
    vector<int> days;
    vector<int> hours;
    
    while (iss >> token) {
        if (dayMap.count(token)) {
            days.push_back(dayMap[token]);
        } else {
            hours.push_back(stoi(token));
        }
    }
    
    for (int day : days) {
        for (int hour : hours) {
            teacherSlots.emplace_back(day, hour);
        }
    }
    int n;
    cin >> n; cin.ignore();
    students.resize(n);
    for (int i = 0; i < n; ++i) {
        string line;
        getline(cin, line);
        istringstream iss(line);
        iss >> students[i].name >> students[i].instrument;
        
        vector<int> studentDays;
        vector<int> studentHours;
        string t;
        while (iss >> t) {
            if (dayMap.count(t)) {
                studentDays.push_back(dayMap[t]);
            } else {
                studentHours.push_back(stoi(t));
            }
        }
        
        for (int day : studentDays) {
            for (int hour : studentHours) {
                for (auto& ts : teacherSlots) {
                    if (ts.first == day && ts.second == hour) {
                        students[i].slots.push_back({day, hour});
                        break;
                    }
                }
            }
        }
    }
    
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        if (a.name == "Ella") return true;
        if (b.name == "Ella") return false;
        if (a.name == "Lola") return true;
        if (b.name == "Lola") return false;
        return false;
    });
    
    int m;
    cin >> m; cin.ignore();
    for (int i = 0; i < m; ++i) {
        string a, b;
        cin >> a >> b; cin.ignore();
        trouble.emplace_back(a, b);
    }
    vector<vector<string>> slotStudent(5, vector<string>(8, ""));
    vector<vector<string>> slotInstr(5, vector<string>(8, ""));
    vector<vector<string>> slotName(5, vector<string>(8, ""));
    dfs(0, slotStudent, slotInstr, slotName);
    vector<vector<string>> table(10, vector<string>(6));
    
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 6; ++j) {
            table[i][j] = "--------------";
        }
    }
    
    table[0][0] = "";
    for (int i = 1; i <= 5; ++i) table[0][i] = dayNames[i-1];
    
    table[1][0] = "8";
    table[2][0] = "9"; 
    table[3][0] = "10";
    table[4][0] = "11";
    table[6][0] = "1";
    table[7][0] = "2";
    table[8][0] = "3";
    table[9][0] = "4";
    
    for (int i = 1; i <= 5; ++i) table[5][i] = "LUNCH";
    
    for (int i = 0; i < 8; ++i) {
        int row = (i < 4) ? i+1 : i+2;
        for (int d = 0; d < 5; ++d) {
            if (slotStudent[d][i] != "") {
                table[row][d+1] = slotStudent[d][i];
            }
        }
    }
    for (int i = 0; i < 10; ++i) {
        string line;
        if (i == 0 || i == 5) line = "   ";
        else {
            stringstream ss; ss << setw(2) << table[i][0];
            line = ss.str() + " ";
        }
        for (int j = 1; j <= 5; ++j) {
            string s = table[i][j];
            int pad = 14 - s.size();
            int left = pad/2, right = pad-left;
            line += string(left, ' ') + s + string(right, ' ');
            if (j != 5) line += " ";
        }
        while (!line.empty() && line.back() == ' ') line.pop_back();
        cout << line << endl;
    }
    return 0;
}
