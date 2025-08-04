#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
using namespace std;

struct Statement {
    string name, location;
    vector<string> companions;
    bool alone;
};

Statement parseStatement(const string& line) {
    Statement stmt;
    size_t colon = line.find(':');
    stmt.name = line.substr(0, colon);
    string rest = line.substr(colon + 2);
    size_t in_pos = rest.find(" in the ");
    if (in_pos == string::npos) in_pos = rest.find(" in ");
    if (in_pos == string::npos) in_pos = rest.find(" at ");
    
    size_t with = rest.find(" with ");
    if (with == string::npos) {
        size_t alone = rest.find(", alone");
        stmt.location = rest.substr(in_pos + 8, alone - in_pos - 8);
        stmt.alone = true;
    } else {
        stmt.location = rest.substr(in_pos + 8, with - in_pos - 8);
        stmt.alone = false;
        string companions = rest.substr(with + 6);
        size_t pos = 0;
        while ((pos = companions.find(" and ")) != string::npos) {
            string comp = companions.substr(0, pos);
            if (comp.back() == '.') comp.pop_back();
            stmt.companions.push_back(comp);
            companions = companions.substr(pos + 5);
        }
        if (!companions.empty()) {
            string comp = companions;
            if (comp.back() == '.') comp.pop_back();
            stmt.companions.push_back(comp);
        }
    }
    return stmt;
}

bool checkConsistency(const vector<Statement>& statements, int exclude) {
    map<string, string> locations;
    map<string, vector<string>> groups;
    
    for (int i = 0; i < statements.size(); i++) {
        if (i == exclude) continue;
        const auto& stmt = statements[i];
        locations[stmt.name] = stmt.location;
        
        if (stmt.alone) {
            if (!groups.count(stmt.location)) groups[stmt.location] = {};
            groups[stmt.location].push_back(stmt.name);
        } else {
            if (!groups.count(stmt.location)) groups[stmt.location] = {};
            groups[stmt.location].push_back(stmt.name);
            for (const string& comp : stmt.companions) {
                if (comp != statements[exclude].name) {
                    groups[stmt.location].push_back(comp);
                }
            }
        }
    }
    
    cerr << "Groups after excluding " << statements[exclude].name << ":" << endl;
    for (const auto& group : groups) {
        cerr << "  " << group.first << ": ";
        for (const string& member : group.second) cerr << member << " ";
        cerr << endl;
    }
    
    for (const auto& group : groups) {
        vector<string> members = group.second;
        sort(members.begin(), members.end());
        members.erase(unique(members.begin(), members.end()), members.end());
        
        for (int i = 0; i < statements.size(); i++) {
            if (i == exclude) continue;
            const auto& stmt = statements[i];
            if (stmt.location == group.first) {
                if (stmt.alone && members.size() != 1) {
                    cerr << "  Inconsistency: " << stmt.name << " claims alone but " << members.size() << " people at " << group.first << endl;
                    return false;
                }
                if (!stmt.alone) {
                    for (const string& comp : stmt.companions) {
                        if (find(members.begin(), members.end(), comp) == members.end()) {
                            cerr << "  Inconsistency: " << stmt.name << " claims to be with " << comp << " but " << comp << " is not at " << group.first << endl;
                            return false;
                        }
                    }
                    if (members.size() != stmt.companions.size() + 1) {
                        cerr << "  Inconsistency: " << stmt.name << " claims " << stmt.companions.size() << " companions but " << members.size() << " people at " << group.first << endl;
                        return false;
                    }
                }
            }
        }
    }
    cerr << "  All consistent!" << endl;
    return true;
}

int main() {
    int n;
    cin >> n; cin.ignore();
    vector<Statement> statements;
    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line);
        statements.push_back(parseStatement(line));
            cerr << "Parsed: " << statements[i].name << " at '" << statements[i].location << "'";
    if (statements[i].alone) cerr << " alone";
    else {
        cerr << " with ";
        for (const string& comp : statements[i].companions) cerr << "'" << comp << "' ";
    }
    cerr << endl;
    }
    
    bool found_killer = false;
    for (int i = 0; i < n; i++) {
        cerr << "Checking if " << statements[i].name << " is killer..." << endl;
        if (checkConsistency(statements, i)) {
            cout << statements[i].name << " did it!" << endl;
            found_killer = true;
            break;
        }
    }
    
    if (!found_killer) {
        cout << "It was me!" << endl;
    }
    return 0;
}
