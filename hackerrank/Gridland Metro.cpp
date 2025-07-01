#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

long long gridlandMetro(int n, int m, int k, vector<vector<int>> track) {
    map<int, vector<pair<int, int>>> rowTracks;
    
    for (int i = 0; i < k; i++) {
        int row = track[i][0];
        int start = track[i][1];
        int end = track[i][2];
        rowTracks[row].push_back(make_pair(start, end));
    }
    
    long long totalOccupied = 0;
    
    for (map<int, vector<pair<int, int>>>::iterator it = rowTracks.begin(); 
         it != rowTracks.end(); ++it) {
        
        vector<pair<int, int>>& tracks = it->second;
        if (tracks.empty()) continue;
        
        sort(tracks.begin(), tracks.end());
        
        vector<pair<int, int>> merged;
        merged.push_back(tracks[0]);
        
        for (size_t i = 1; i < tracks.size(); i++) {
            int currentStart = tracks[i].first;
            int currentEnd = tracks[i].second;
            int lastEnd = merged.back().second;
            
            if (currentStart <= lastEnd) {
                merged.back().second = max(lastEnd, currentEnd);
            } else {
                merged.push_back(make_pair(currentStart, currentEnd));
            }
        }
        
        for (size_t i = 0; i < merged.size(); i++) {
            totalOccupied += (long long)(merged[i].second - merged[i].first + 1);
        }
    }
    
    return (long long)n * (long long)m - totalOccupied;
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

    vector<vector<int>> track(k);

    for (int i = 0; i < k; i++) {
        track[i].resize(3);

        string track_row_temp_temp;
        getline(cin, track_row_temp_temp);

        vector<string> track_row_temp = split(rtrim(track_row_temp_temp));

        for (int j = 0; j < 3; j++) {
            int track_row_item = stoi(track_row_temp[j]);

            track[i][j] = track_row_item;
        }
    }

    long long result = gridlandMetro(n, m, k, track);

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
