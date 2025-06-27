#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <sstream>
#include <queue>

using namespace std;

vector<string> parseImports(int n_imp) {
    vector<string> imports;
    for (int i = 0; i < n_imp; i++) {
        string import;
        getline(cin, import);
        string lib = import.substr(7);
        imports.push_back(lib);
    }
    return imports;
}

map<string, vector<string>> parseDependencies(int n_dep) {
    map<string, vector<string>> deps;
    for (int i = 0; i < n_dep; i++) {
        string dependency;
        getline(cin, dependency);
        
        size_t requiresPos = dependency.find(" requires ");
        string lib = dependency.substr(0, requiresPos);
        string reqPart = dependency.substr(requiresPos + 10);
        
        vector<string> required;
        stringstream ss(reqPart);
        string item;
        while (getline(ss, item, ',')) {
            item.erase(0, item.find_first_not_of(" "));
            item.erase(item.find_last_not_of(" ") + 1);
            required.push_back(item);
        }
        deps[lib] = required;
    }
    return deps;
}

bool canImport(const vector<string>& imports, const map<string, vector<string>>& deps, 
               string& errorLib1, string& errorLib2) {
    set<string> imported;
    
    for (const string& lib : imports) {
        if (deps.count(lib)) {
            for (const string& req : deps.at(lib)) {
                if (imported.find(req) == imported.end()) {
                    errorLib1 = lib;
                    errorLib2 = req;
                    return false;
                }
            }
        }
        imported.insert(lib);
    }
    return true;
}

bool hasCycle(const vector<string>& libs, const map<string, vector<string>>& deps) {
    map<string, int> state;
    
    function<bool(const string&)> dfs = [&](const string& lib) -> bool {
        if (state[lib] == 1) return true;
        if (state[lib] == 2) return false;
        
        state[lib] = 1;
        if (deps.count(lib)) {
            for (const string& req : deps.at(lib)) {
                if (dfs(req)) return true;
            }
        }
        state[lib] = 2;
        return false;
    };
    
    for (const string& lib : libs) {
        if (state[lib] == 0 && dfs(lib)) {
            return true;
        }
    }
    return false;
}

vector<string> topologicalSort(const vector<string>& libs, const map<string, vector<string>>& deps) {
    map<string, int> indegree;
    map<string, vector<string>> graph;
    
    for (const string& lib : libs) {
        indegree[lib] = 0;
    }
    
    for (const string& lib : libs) {
        if (deps.count(lib)) {
            for (const string& req : deps.at(lib)) {
                graph[req].push_back(lib);
                indegree[lib]++;
            }
        }
    }
    
    priority_queue<string, vector<string>, greater<string>> pq;
    for (const string& lib : libs) {
        if (indegree[lib] == 0) {
            pq.push(lib);
        }
    }
    
    vector<string> result;
    while (!pq.empty()) {
        string current = pq.top();
        pq.pop();
        result.push_back(current);
        
        for (const string& neighbor : graph[current]) {
            indegree[neighbor]--;
            if (indegree[neighbor] == 0) {
                pq.push(neighbor);
            }
        }
    }
    
    return result;
}

int main() {
    int n_imp;
    cin >> n_imp;
    cin.ignore();
    
    vector<string> imports = parseImports(n_imp);
    
    int n_dep;
    cin >> n_dep;
    cin.ignore();
    
    map<string, vector<string>> deps = parseDependencies(n_dep);
    
    string errorLib1, errorLib2;
    if (canImport(imports, deps, errorLib1, errorLib2)) {
        cout << "Compiled successfully!" << endl;
        return 0;
    }
    
    cout << "Import error: tried to import " << errorLib1 << " but " << errorLib2 << " is required." << endl;
    
    if (hasCycle(imports, deps)) {
        cout << "Fatal error: interdependencies." << endl;
        return 0;
    }
    
    vector<string> sorted = topologicalSort(imports, deps);
    cout << "Suggest to change import order:" << endl;
    for (const string& lib : sorted) {
        cout << "import " << lib << endl;
    }
    
    return 0;
}
