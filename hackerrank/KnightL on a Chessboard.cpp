#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

int bfsKnight(int n, int a, int b);

vector<vector<int>> knightlOnAChessboard(int n) {
    vector<vector<int>> result(n-1, vector<int>(n-1));
    
    for (int a = 1; a < n; a++) {
        for (int b = 1; b < n; b++) {
            result[a-1][b-1] = bfsKnight(n, a, b);
        }
    }
    
    return result;
}

int bfsKnight(int n, int a, int b) {
    if (n == 1) return 0;
    
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    vector<vector<int>> dist(n, vector<int>(n, 0));
    queue<pair<int, int>> q;
    
    q.push(make_pair(0, 0));
    visited[0][0] = true;
    dist[0][0] = 0;
    
    int dx[8] = {a, a, -a, -a, b, b, -b, -b};
    int dy[8] = {b, -b, b, -b, a, -a, a, -a};
    
    while (!q.empty()) {
        pair<int, int> current = q.front();
        q.pop();
        
        int x = current.first;
        int y = current.second;
        
        if (x == n-1 && y == n-1) {
            return dist[x][y];
        }
        
        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if (nx >= 0 && nx < n && ny >= 0 && ny < n && !visited[nx][ny]) {
                visited[nx][ny] = true;
                dist[nx][ny] = dist[x][y] + 1;
                q.push(make_pair(nx, ny));
            }
        }
    }
    
    return -1;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<vector<int>> result = knightlOnAChessboard(n);

    for (size_t i = 0; i < result.size(); i++) {
        for (size_t j = 0; j < result[i].size(); j++) {
            fout << result[i][j];

            if (j != result[i].size() - 1) {
                fout << " ";
            }
        }

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

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
