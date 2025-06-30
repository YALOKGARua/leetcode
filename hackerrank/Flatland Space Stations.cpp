#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

class FlatlandDistanceCalculator {
private:
    static int findDistanceToNearestStation(int cityIndex, const vector<int>& sortedStations) {
        auto lowerBoundIterator = lower_bound(sortedStations.begin(), sortedStations.end(), cityIndex);
        
        int minimumDistance = INT_MAX;
        
        if (lowerBoundIterator != sortedStations.end()) {
            minimumDistance = min(minimumDistance, abs(cityIndex - *lowerBoundIterator));
        }
        
        if (lowerBoundIterator != sortedStations.begin()) {
            --lowerBoundIterator;
            minimumDistance = min(minimumDistance, abs(cityIndex - *lowerBoundIterator));
        }
        
        return minimumDistance;
    }
    
    static int calculateMaxDistanceOptimized(int totalCities, const vector<int>& stationPositions) {
        vector<int> sortedStations = stationPositions;
        sort(sortedStations.begin(), sortedStations.end());
        
        int maxDistanceFound = 0;
        
        for (int cityIndex = 0; cityIndex < totalCities; ++cityIndex) {
            int distanceToNearest = findDistanceToNearestStation(cityIndex, sortedStations);
            maxDistanceFound = max(maxDistanceFound, distanceToNearest);
        }
        
        return maxDistanceFound;
    }
    
    static int calculateMaxDistanceSegmentBased(int totalCities, const vector<int>& stationPositions) {
        vector<int> sortedStations = stationPositions;
        sort(sortedStations.begin(), sortedStations.end());
        
        int maxDistanceFound = 0;
        
        if (sortedStations[0] > 0) {
            maxDistanceFound = max(maxDistanceFound, sortedStations[0]);
        }
        
        for (int stationIndex = 1; stationIndex < sortedStations.size(); ++stationIndex) {
            int segmentLength = sortedStations[stationIndex] - sortedStations[stationIndex - 1];
            int maxDistanceInSegment = segmentLength / 2;
            maxDistanceFound = max(maxDistanceFound, maxDistanceInSegment);
        }
        
        if (sortedStations.back() < totalCities - 1) {
            maxDistanceFound = max(maxDistanceFound, (totalCities - 1) - sortedStations.back());
        }
        
        return maxDistanceFound;
    }
    
public:
    static int computeMaximalDistanceToStations(int totalCities, const vector<int>& stationLocations) {
        if (stationLocations.size() == totalCities) {
            return 0;
        }
        
        return calculateMaxDistanceSegmentBased(totalCities, stationLocations);
    }
};

int flatlandSpaceStations(int n, vector<int> c) {
    return FlatlandDistanceCalculator::computeMaximalDistanceToStations(n, c);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nm_temp;
    getline(cin, nm_temp);

    vector<string> nm = split_string(nm_temp);

    int n = stoi(nm[0]);

    int m = stoi(nm[1]);

    string c_temp_temp;
    getline(cin, c_temp_temp);

    vector<string> c_temp = split_string(c_temp_temp);

    vector<int> c(m);

    for (int i = 0; i < m; i++) {
        int c_item = stoi(c_temp[i]);

        c[i] = c_item;
    }

    int result = flatlandSpaceStations(n, c);

    fout << result << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
