#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

void printShortestPath(int n, int i_start, int j_start, int i_end, int j_end) {
    const vector<pair<int, int>> directions = {{-2, -1}, {-2, 1}, {0, 2}, {2, 1}, {2, -1}, {0, -2}};
    const vector<string> moveNames = {"UL", "UR", "R", "LR", "LL", "L"};
    
    struct StateNode {
        int row, col, distance;
        vector<string> pathSequence;
        
        StateNode(int r, int c, int d, vector<string> path) 
            : row(r), col(c), distance(d), pathSequence(move(path)) {}
    };
    
    auto isValidPosition = [&](int row, int col) -> bool {
        return row >= 0 && row < n && col >= 0 && col < n;
    };
    
    auto encodePosition = [&](int row, int col) -> long long {
        return static_cast<long long>(row) * n + col;
    };
    
    unordered_set<long long> visitedPositions;
    queue<StateNode> explorationQueue;
    
    explorationQueue.emplace(i_start, j_start, 0, vector<string>());
    visitedPositions.insert(encodePosition(i_start, j_start));
    
    while (!explorationQueue.empty()) {
        StateNode currentState = move(explorationQueue.front());
        explorationQueue.pop();
        
        if (currentState.row == i_end && currentState.col == j_end) {
            cout << currentState.distance << "\n";
            for (size_t i = 0; i < currentState.pathSequence.size(); ++i) {
                if (i > 0) cout << " ";
                cout << currentState.pathSequence[i];
            }
            cout << "\n";
            return;
        }
        
        for (size_t moveIndex = 0; moveIndex < directions.size(); ++moveIndex) {
            int nextRow = currentState.row + directions[moveIndex].first;
            int nextCol = currentState.col + directions[moveIndex].second;
            
            if (!isValidPosition(nextRow, nextCol)) continue;
            
            long long nextPositionKey = encodePosition(nextRow, nextCol);
            if (visitedPositions.find(nextPositionKey) != visitedPositions.end()) continue;
            
            vector<string> extendedPath = currentState.pathSequence;
            extendedPath.push_back(moveNames[moveIndex]);
            
            explorationQueue.emplace(nextRow, nextCol, currentState.distance + 1, move(extendedPath));
            visitedPositions.insert(nextPositionKey);
        }
    }
    
    cout << "Impossible\n";
}

int main()
{
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int i_start = stoi(first_multiple_input[0]);

    int j_start = stoi(first_multiple_input[1]);

    int i_end = stoi(first_multiple_input[2]);

    int j_end = stoi(first_multiple_input[3]);

    printShortestPath(n, i_start, j_start, i_end, j_end);

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
