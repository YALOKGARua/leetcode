#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

vector<int> roadWidthSegments;

class ServiceLaneProcessor {
private:
    static int findMinimumWidthInSegment(int startPosition, int endPosition) {
        int minimumWidth = INT_MAX;
        
        for (int currentIndex = startPosition; currentIndex <= endPosition; ++currentIndex) {
            minimumWidth = min(minimumWidth, roadWidthSegments[currentIndex]);
            
            if (minimumWidth == 1) {
                return minimumWidth;
            }
        }
        
        return minimumWidth;
    }
    
public:
    static vector<int> analyzeVehiclePassageRequests(const vector<vector<int>>& querySegments) {
        vector<int> maximumVehicleWidths;
        maximumVehicleWidths.reserve(querySegments.size());
        
        for (const auto& segmentQuery : querySegments) {
            int entryIndex = segmentQuery[0];
            int exitIndex = segmentQuery[1];
            
            int bottleneckWidth = findMinimumWidthInSegment(entryIndex, exitIndex);
            maximumVehicleWidths.emplace_back(bottleneckWidth);
        }
        
        return maximumVehicleWidths;
    }
};

vector<int> serviceLane(int n, vector<vector<int>> cases) {
    return ServiceLaneProcessor::analyzeVehiclePassageRequests(cases);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int t = stoi(first_multiple_input[1]);

    string width_temp_temp;
    getline(cin, width_temp_temp);

    vector<string> width_temp = split(rtrim(width_temp_temp));

    vector<int> width(n);

    for (int i = 0; i < n; i++) {
        int width_item = stoi(width_temp[i]);
        width[i] = width_item;
    }

    vector<vector<int>> cases(t);

    for (int i = 0; i < t; i++) {
        cases[i].resize(2);

        string cases_row_temp_temp;
        getline(cin, cases_row_temp_temp);

        vector<string> cases_row_temp = split(rtrim(cases_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int cases_row_item = stoi(cases_row_temp[j]);

            cases[i][j] = cases_row_item;
        }
    }

    roadWidthSegments = width;
    vector<int> result = serviceLane(n, cases);

    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];

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
