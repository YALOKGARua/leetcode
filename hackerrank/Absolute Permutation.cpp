#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

class AbsolutePermutationSolver {
private:
    static bool canConstructValidPermutation(int sequenceLength, int absoluteDifference) {
        if (absoluteDifference == 0) {
            return true;
        }
        
        if (sequenceLength % (2 * absoluteDifference) != 0) {
            return false;
        }
        
        return true;
    }
    
    static vector<int> constructTrivialPermutation(int n) {
        vector<int> identityPermutation(n);
        for (int position = 0; position < n; ++position) {
            identityPermutation[position] = position + 1;
        }
        return identityPermutation;
    }
    
    static vector<int> constructPairwiseSwappedPermutation(int sequenceLength, int swapDistance) {
        vector<int> resultPermutation(sequenceLength);
        
        for (int blockStart = 1; blockStart <= sequenceLength; blockStart += 2 * swapDistance) {
            for (int positionOffset = 0; positionOffset < swapDistance; ++positionOffset) {
                int firstPosition = blockStart + positionOffset;
                int secondPosition = firstPosition + swapDistance;
                
                if (secondPosition <= sequenceLength) {
                    resultPermutation[firstPosition - 1] = secondPosition;
                    resultPermutation[secondPosition - 1] = firstPosition;
                }
            }
        }
        
        return resultPermutation;
    }
    
public:
    static vector<int> generateAbsolutePermutation(int n, int k) {
        if (!canConstructValidPermutation(n, k)) {
            return {-1};
        }
        
        if (k == 0) {
            return constructTrivialPermutation(n);
        }
        
        return constructPairwiseSwappedPermutation(n, k);
    }
};

class MathematicalPermutationAnalyzer {
private:
    static bool validatePermutationExistence(int totalElements, int targetDifference) {
        if (targetDifference == 0) return true;
        
        return (totalElements % (2 * targetDifference)) == 0;
    }
    
    static vector<int> buildOptimalPermutation(int n, int k) {
        vector<int> permutation(n);
        
        if (k == 0) {
            iota(permutation.begin(), permutation.end(), 1);
            return permutation;
        }
        
        for (int segmentStart = 0; segmentStart < n; segmentStart += 2 * k) {
            for (int innerIndex = 0; innerIndex < k && segmentStart + innerIndex < n; ++innerIndex) {
                int leftPosition = segmentStart + innerIndex;
                int rightPosition = leftPosition + k;
                
                if (rightPosition < n) {
                    permutation[leftPosition] = rightPosition + 1;
                    permutation[rightPosition] = leftPosition + 1;
                }
            }
        }
        
        return permutation;
    }
    
public:
    static vector<int> solveAbsolutePermutationProblem(int n, int k) {
        if (!validatePermutationExistence(n, k)) {
            return {-1};
        }
        
        return buildOptimalPermutation(n, k);
    }
};

vector<int> absolutePermutation(int n, int k) {
    return AbsolutePermutationSolver::generateAbsolutePermutation(n, k);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        int k = stoi(first_multiple_input[1]);

        vector<int> result = absolutePermutation(n, k);

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
