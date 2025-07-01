#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

class BipartiteMatching {
private:
    vector<vector<int>> graph;
    vector<int> match;
    vector<bool> used;
    int n, m;
    
    bool dfs(int v) {
        if (used[v]) return false;
        used[v] = true;
        
        for (int to : graph[v]) {
            if (match[to] == -1 || dfs(match[to])) {
                match[to] = v;
                return true;
            }
        }
        return false;
    }
    
public:
    BipartiteMatching(int bikers_count, int bikes_count) : 
        n(bikers_count), m(bikes_count) {
        graph.assign(n, vector<int>());
        match.assign(m, -1);
        used.assign(n, false);
    }
    
    void addEdge(int biker, int bike) {
        graph[biker].push_back(bike);
    }
    
    int maxMatching() {
        fill(match.begin(), match.end(), -1);
        int result = 0;
        
        for (int v = 0; v < n; ++v) {
            fill(used.begin(), used.end(), false);
            if (dfs(v)) result++;
        }
        return result;
    }
    
    void clearEdges() {
        for (auto& adj : graph) {
            adj.clear();
        }
    }
};

long distanceSquared(const vector<int>& biker, const vector<int>& bike) {
    long dx = biker[0] - bike[0];
    long dy = biker[1] - bike[1];
    return dx * dx + dy * dy;
}

bool canAssignWithMaxTime(const vector<vector<int>>& bikers, 
                         const vector<vector<int>>& bikes, 
                         int k, long maxTimeSquared) {
    int n = bikers.size();
    int m = bikes.size();
    
    BipartiteMatching matcher(n, m);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (distanceSquared(bikers[i], bikes[j]) <= maxTimeSquared) {
                matcher.addEdge(i, j);
            }
        }
    }
    
    return matcher.maxMatching() >= k;
}

long bikeRacers(vector<vector<int>> bikers, vector<vector<int>> bikes, int k) {
    int n = bikers.size();
    int m = bikes.size();
    
    vector<long> distances;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            distances.push_back(distanceSquared(bikers[i], bikes[j]));
        }
    }
    
    sort(distances.begin(), distances.end());
    distances.erase(unique(distances.begin(), distances.end()), distances.end());
    
    long left = 0, right = distances.size() - 1;
    long answer = distances.back();
    
    while (left <= right) {
        long mid = left + (right - left) / 2;
        long timeSquared = distances[mid];
        
        if (canAssignWithMaxTime(bikers, bikes, k, timeSquared)) {
            answer = timeSquared;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    return answer;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int m = stoi(first_multiple_input[1]);

    int k = stoi(first_multiple_input[2]);

    vector<vector<int>> bikers(n);

    for (int i = 0; i < n; i++) {
        bikers[i].resize(2);

        string bikers_row_temp_temp;
        getline(cin, bikers_row_temp_temp);

        vector<string> bikers_row_temp = split(rtrim(bikers_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int bikers_row_item = stoi(bikers_row_temp[j]);

            bikers[i][j] = bikers_row_item;
        }
    }

    vector<vector<int>> bikes(m);

    for (int i = 0; i < m; i++) {
        bikes[i].resize(2);

        string bikes_row_temp_temp;
        getline(cin, bikes_row_temp_temp);

        vector<string> bikes_row_temp = split(rtrim(bikes_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int bikes_row_item = stoi(bikes_row_temp[j]);

            bikes[i][j] = bikes_row_item;
        }
    }

    long result = bikeRacers(bikers, bikes, k);

    fout << result << "\n";

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
