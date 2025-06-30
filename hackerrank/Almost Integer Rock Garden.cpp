#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

class GeometricDistanceCalculator {
public:
    static double calculateDistance(int x, int y) {
        return sqrt(static_cast<double>(x * x + y * y));
    }
    
    static bool isIntegerDistance(int x, int y) {
        long long squared = static_cast<long long>(x) * x + static_cast<long long>(y) * y;
        long long root = static_cast<long long>(sqrt(squared));
        return root * root == squared;
    }
    
    static bool isAlmostInteger(double value, double tolerance = 0.5) {
        double nearestInt = round(value);
        return abs(value - nearestInt) < tolerance;
    }
};

class CoordinateGenerator {
private:
    static constexpr int MAX_COORD = 15;
    static constexpr int MIN_COORD = -15;
    
public:
    static vector<pair<int, int>> generateCandidates(int excludeX, int excludeY) {
        vector<pair<int, int>> candidates;
        
        for (int x = MIN_COORD; x <= MAX_COORD; x++) {
            for (int y = MIN_COORD; y <= MAX_COORD; y++) {
                if (x == excludeX && y == excludeY) continue;
                if (x == 0 && y == 0) continue;
                if (!GeometricDistanceCalculator::isIntegerDistance(x, y)) {
                    candidates.emplace_back(x, y);
                }
            }
        }
        
        return candidates;
    }
};

class OptimalPlacementFinder {
public:
    struct PlacementResult {
        vector<pair<int, int>> positions;
        double totalSum;
        bool isValid;
        
        PlacementResult() : isValid(false) {}
        PlacementResult(const vector<pair<int, int>>& pos, double sum) 
            : positions(pos), totalSum(sum), isValid(true) {}
    };

private:
    vector<pair<int, int>> candidates;
    double firstDistance;
    
public:
    OptimalPlacementFinder(int firstX, int firstY) {
        firstDistance = GeometricDistanceCalculator::calculateDistance(firstX, firstY);
        candidates = CoordinateGenerator::generateCandidates(firstX, firstY);
        
        sort(candidates.begin(), candidates.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            double distA = GeometricDistanceCalculator::calculateDistance(a.first, a.second);
            double distB = GeometricDistanceCalculator::calculateDistance(b.first, b.second);
            return distA < distB;
        });
    }
    
    PlacementResult findOptimalPlacement() {
        vector<double> distances;
        for (const auto& coord : candidates) {
            distances.push_back(GeometricDistanceCalculator::calculateDistance(coord.first, coord.second));
        }
        
        return searchOptimalCombination(distances);
    }
    
private:
    PlacementResult searchOptimalCombination(const vector<double>& distances) {
        double targetSum = round(firstDistance);
        
        for (int offset = -5; offset <= 5; offset++) {
            double currentTarget = targetSum + offset - firstDistance;
            PlacementResult result = findCombinationForTarget(currentTarget, distances);
            if (result.isValid) return result;
        }
        
        return generateFallbackSolution();
    }
    
    PlacementResult findCombinationForTarget(double target, const vector<double>& distances) {
        vector<int> indices(11);
        return recursiveSearch(target, distances, indices, 0, 0, 0.0);
    }
    
    PlacementResult recursiveSearch(double target, const vector<double>& distances, 
                                  vector<int>& indices, int pos, int start, double current) {
        if (pos == 11) {
            if (GeometricDistanceCalculator::isAlmostInteger(current + firstDistance)) {
                vector<pair<int, int>> positions;
                for (int i = 0; i < 11; i++) {
                    positions.push_back(candidates[indices[i]]);
                }
                return PlacementResult(positions, current + firstDistance);
            }
            return PlacementResult();
        }
        
        for (int i = start; i < min(static_cast<int>(distances.size()), start + 100); i++) {
            indices[pos] = i;
            PlacementResult result = recursiveSearch(target, distances, indices, pos + 1, i + 1, current + distances[i]);
            if (result.isValid) return result;
        }
        
        return PlacementResult();
    }
    
    PlacementResult generateFallbackSolution() {
        vector<pair<int, int>> fallbackPositions = {
            {1, 11}, {11, 1}, {-2, 12}, {5, 4}, {12, -3},
            {10, 3}, {9, 6}, {-12, -7}, {-6, -6}, {12, -4}, {4, 12}
        };
        
        double sum = firstDistance;
        for (const auto& pos : fallbackPositions) {
            sum += GeometricDistanceCalculator::calculateDistance(pos.first, pos.second);
        }
        
        return PlacementResult(fallbackPositions, sum);
    }
};

class SmartRockGardenGenerator {
public:
    static bool hasIntegerDistance(int x, int y) {
        long long squared = static_cast<long long>(x) * x + static_cast<long long>(y) * y;
        long long root = static_cast<long long>(sqrt(squared) + 0.5);
        return root * root == squared;
    }
    
    static double getDistance(int x, int y) {
        return sqrt(static_cast<double>(x) * x + static_cast<double>(y) * y);
    }
    
    static vector<pair<int, int>> generateValidPoints(int excludeX, int excludeY) {
        vector<pair<int, int>> candidates;
        
        for (int x = -15; x <= 15; x++) {
            for (int y = -15; y <= 15; y++) {
                if (x == excludeX && y == excludeY) continue;
                if (x == 0 && y == 0) continue;
                if (!hasIntegerDistance(x, y)) {
                    candidates.push_back(make_pair(x, y));
                }
            }
        }
        
        return candidates;
    }
    
    static bool isAlmostInteger(double value) {
        double nearest = round(value);
        return abs(value - nearest) <= 0.5;
    }
};

class OptimizedRockSolver {
public:
    static void solve(int firstX, int firstY) {
        vector<pair<int, int>> candidates = SmartRockGardenGenerator::generateValidPoints(firstX, firstY);
        double firstDist = SmartRockGardenGenerator::getDistance(firstX, firstY);
        
        vector<pair<int, int>> result;
        double targetSum = round(firstDist);
        double remaining = targetSum - firstDist;
        
        sort(candidates.begin(), candidates.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            return SmartRockGardenGenerator::getDistance(a.first, a.second) < 
                   SmartRockGardenGenerator::getDistance(b.first, b.second);
        });
        
        if (findSolutionGreedy(candidates, remaining, result) || 
            findSolutionWithOffset(candidates, firstDist, result)) {
            for (const pair<int, int>& pos : result) {
                cout << pos.first << " " << pos.second << endl;
            }
        } else {
            generateFallbackSolution(candidates);
        }
    }
    
private:
    static bool findSolutionGreedy(const vector<pair<int, int>>& candidates, 
                                 double target, vector<pair<int, int>>& result) {
        result.clear();
        double currentSum = 0.0;
        
        for (const pair<int, int>& candidate : candidates) {
            if (result.size() >= 11) break;
            
            double dist = SmartRockGardenGenerator::getDistance(candidate.first, candidate.second);
            if (currentSum + dist <= target + 5.0) {
                result.push_back(candidate);
                currentSum += dist;
            }
        }
        
        return result.size() == 11;
    }
    
    static bool findSolutionWithOffset(const vector<pair<int, int>>& candidates,
                                     double firstDist, vector<pair<int, int>>& result) {
        for (int offset = -10; offset <= 10; offset++) {
            double targetTotal = round(firstDist) + offset;
            double remaining = targetTotal - firstDist;
            
            if (findSolutionGreedy(candidates, remaining, result)) {
                double totalSum = firstDist;
                for (const pair<int, int>& pos : result) {
                    totalSum += SmartRockGardenGenerator::getDistance(pos.first, pos.second);
                }
                
                if (SmartRockGardenGenerator::isAlmostInteger(totalSum)) {
                    return true;
                }
            }
        }
        return false;
    }
    
    static void generateFallbackSolution(const vector<pair<int, int>>& candidates) {
        for (int i = 0; i < min(11, static_cast<int>(candidates.size())); i++) {
            cout << candidates[i].first << " " << candidates[i].second << endl;
        }
    }
};

class AdvancedRockGardenSolver {
public:
    static void solve(int firstX, int firstY) {
        OptimizedRockSolver::solve(firstX, firstY);
    }
};

class MathematicalPatternGenerator {
public:
    static vector<pair<int, int>> generatePatternBasedSolution(int firstX, int firstY) {
        vector<pair<int, int>> patterns;
        
        vector<pair<int, int>> basePatterns = {
            {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6},
            {6, 7}, {7, 8}, {8, 9}, {9, 10}, {10, 11}, {11, 12}
        };
        
        for (pair<int, int>& pattern : basePatterns) {
            int x = pattern.first;
            int y = pattern.second;
            
            if (x == firstX && y == firstY) {
                x = -x;
                y = y + 1;
            }
            
            if (!GeometricDistanceCalculator::isIntegerDistance(x, y)) {
                patterns.emplace_back(x, y);
            }
        }
        
        while (patterns.size() < 11) {
            patterns.emplace_back(patterns.size() + 1, patterns.size() + 2);
        }
        
        patterns.resize(11);
        return patterns;
    }
};

int main()
{
    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int x = stoi(first_multiple_input[0]);
    int y = stoi(first_multiple_input[1]);

    AdvancedRockGardenSolver::solve(x, y);

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
