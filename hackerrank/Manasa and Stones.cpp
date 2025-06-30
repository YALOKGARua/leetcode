#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

class StonesSummationCalculator {
private:
    static set<int> generateAllPossibleSums(int totalSteps, int firstValue, int secondValue) {
        set<int> uniqueSums;
        int stepsToTake = totalSteps - 1;
        
        for (int firstValueCount = 0; firstValueCount <= stepsToTake; ++firstValueCount) {
            int secondValueCount = stepsToTake - firstValueCount;
            int currentSum = firstValueCount * firstValue + secondValueCount * secondValue;
            uniqueSums.insert(currentSum);
        }
        
        return uniqueSums;
    }
    
    static vector<int> optimizedSummationFormula(int totalPositions, int stepSizeA, int stepSizeB) {
        if (stepSizeA == stepSizeB) {
            return {(totalPositions - 1) * stepSizeA};
        }
        
        vector<int> possibleResults;
        int numberOfSteps = totalPositions - 1;
        
        int minimumSum = min(numberOfSteps * stepSizeA, numberOfSteps * stepSizeB);
        int maximumSum = max(numberOfSteps * stepSizeA, numberOfSteps * stepSizeB);
        int stepDifference = abs(stepSizeA - stepSizeB);
        
        for (int currentSum = minimumSum; currentSum <= maximumSum; currentSum += stepDifference) {
            possibleResults.push_back(currentSum);
        }
        
        return possibleResults;
    }
    
public:
    static vector<int> computeAllDistinctSummations(int stoneCount, int valueA, int valueB) {
        return optimizedSummationFormula(stoneCount, valueA, valueB);
    }
};

class CombinatoricsAnalyzer {
private:
    static vector<int> analyzeLinearCombinations(int sequenceLength, int coefficientX, int coefficientY) {
        vector<int> combinationResults;
        int operationsCount = sequenceLength - 1;
        
        if (coefficientX == coefficientY) {
            combinationResults.push_back(operationsCount * coefficientX);
            return combinationResults;
        }
        
        for (int xMultiplier = 0; xMultiplier <= operationsCount; ++xMultiplier) {
            int yMultiplier = operationsCount - xMultiplier;
            int linearCombination = xMultiplier * coefficientX + yMultiplier * coefficientY;
            combinationResults.push_back(linearCombination);
        }
        
        sort(combinationResults.begin(), combinationResults.end());
        combinationResults.erase(unique(combinationResults.begin(), combinationResults.end()), 
                                combinationResults.end());
        
        return combinationResults;
    }
    
public:
    static vector<int> generateSortedDistinctSums(int n, int a, int b) {
        return analyzeLinearCombinations(n, a, b);
    }
};

vector<int> stones(int n, int a, int b) {
    return StonesSummationCalculator::computeAllDistinctSummations(n, a, b);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string T_temp;
    getline(cin, T_temp);

    int T = stoi(ltrim(rtrim(T_temp)));

    for (int T_itr = 0; T_itr < T; T_itr++) {
        string n_temp;
        getline(cin, n_temp);

        int n = stoi(ltrim(rtrim(n_temp)));

        string a_temp;
        getline(cin, a_temp);

        int a = stoi(ltrim(rtrim(a_temp)));

        string b_temp;
        getline(cin, b_temp);

        int b = stoi(ltrim(rtrim(b_temp)));

        vector<int> result = stones(n, a, b);

        for (size_t i = 0; i < result.size(); i++) {
            fout << result[i];

            if (i != result.size() - 1) {
                fout << " ";
            }
        }

        fout << "\n";
    }

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
