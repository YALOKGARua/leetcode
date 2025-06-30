#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

template<typename T>
class ArrayDifferenceAnalyzer {
public:
    struct DifferencePoint {
        int index;
        T originalValue;
        T expectedValue;
        
        DifferencePoint(int i, T orig, T exp) 
            : index(i), originalValue(orig), expectedValue(exp) {}
    };
    
    static vector<DifferencePoint> findDifferences(const vector<T>& original, const vector<T>& sorted) {
        vector<DifferencePoint> differences;
        
        for (int i = 0; i < original.size(); i++) {
            if (original[i] != sorted[i]) {
                differences.emplace_back(i, original[i], sorted[i]);
            }
        }
        
        return differences;
    }
    
    static pair<int, int> findDifferenceRange(const vector<T>& original, const vector<T>& sorted) {
        int left = -1, right = -1;
        
        for (int i = 0; i < original.size(); i++) {
            if (original[i] != sorted[i]) {
                if (left == -1) left = i;
                right = i;
            }
        }
        
        return {left, right};
    }
};

class SortingOperationValidator {
public:
    enum class OperationType {
        ALREADY_SORTED,
        SWAP_OPERATION,
        REVERSE_OPERATION,
        IMPOSSIBLE
    };
    
    struct ValidationResult {
        OperationType operation;
        int leftIndex;
        int rightIndex;
        bool isValid;
        
        ValidationResult(OperationType op, int left = -1, int right = -1) 
            : operation(op), leftIndex(left), rightIndex(right), isValid(op != OperationType::IMPOSSIBLE) {}
    };
    
    static ValidationResult validateSwapOperation(const vector<int>& arr, const vector<int>& sorted) {
        auto differences = ArrayDifferenceAnalyzer<int>::findDifferences(arr, sorted);
        
        if (differences.size() == 0) {
            return ValidationResult(OperationType::ALREADY_SORTED);
        }
        
        if (differences.size() != 2) {
            return ValidationResult(OperationType::IMPOSSIBLE);
        }
        
        int pos1 = differences[0].index;
        int pos2 = differences[1].index;
        
        if (arr[pos1] == sorted[pos2] && arr[pos2] == sorted[pos1]) {
            return ValidationResult(OperationType::SWAP_OPERATION, pos1, pos2);
        }
        
        return ValidationResult(OperationType::IMPOSSIBLE);
    }
    
    static ValidationResult validateReverseOperation(const vector<int>& arr, const vector<int>& sorted) {
        auto [left, right] = ArrayDifferenceAnalyzer<int>::findDifferenceRange(arr, sorted);
        
        if (left == -1) {
            return ValidationResult(OperationType::ALREADY_SORTED);
        }
        
        vector<int> testArray = arr;
        reverse(testArray.begin() + left, testArray.begin() + right + 1);
        
        if (testArray == sorted) {
            return ValidationResult(OperationType::REVERSE_OPERATION, left, right);
        }
        
        return ValidationResult(OperationType::IMPOSSIBLE);
    }
};

class AlmostSortedSolver {
private:
    SortingOperationValidator validator;
    
    static bool isAlreadySorted(const vector<int>& arr) {
        return is_sorted(arr.begin(), arr.end());
    }
    
    static vector<int> createSortedCopy(vector<int> arr) {
        sort(arr.begin(), arr.end());
        return arr;
    }
    
public:
    void solve(vector<int> arr) {
        if (isAlreadySorted(arr)) {
            cout << "yes" << endl;
            return;
        }
        
        vector<int> sortedArr = createSortedCopy(arr);
        
        auto swapResult = validator.validateSwapOperation(arr, sortedArr);
        auto reverseResult = validator.validateReverseOperation(arr, sortedArr);
        
        if (swapResult.isValid) {
            cout << "yes" << endl;
            cout << "swap " << (swapResult.leftIndex + 1) << " " << (swapResult.rightIndex + 1) << endl;
        } else if (reverseResult.isValid) {
            cout << "yes" << endl;
            cout << "reverse " << (reverseResult.leftIndex + 1) << " " << (reverseResult.rightIndex + 1) << endl;
        } else {
            cout << "no" << endl;
        }
    }
};

class OptimizedAlmostSortedAnalyzer {
public:
    static void analyzeAndSolve(vector<int> arr) {
        vector<int> sorted = arr;
        sort(sorted.begin(), sorted.end());
        
        vector<int> mismatchIndices;
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] != sorted[i]) {
                mismatchIndices.push_back(i);
            }
        }
        
        if (mismatchIndices.empty()) {
            cout << "yes" << endl;
            return;
        }
        
        if (mismatchIndices.size() == 2) {
            int pos1 = mismatchIndices[0];
            int pos2 = mismatchIndices[1];
            
            if (arr[pos1] == sorted[pos2] && arr[pos2] == sorted[pos1]) {
                cout << "yes" << endl;
                cout << "swap " << (pos1 + 1) << " " << (pos2 + 1) << endl;
                return;
            }
        }
        
        int left = mismatchIndices.front();
        int right = mismatchIndices.back();
        
        vector<int> testArr = arr;
        reverse(testArr.begin() + left, testArr.begin() + right + 1);
        
        if (testArr == sorted) {
            cout << "yes" << endl;
            cout << "reverse " << (left + 1) << " " << (right + 1) << endl;
        } else {
            cout << "no" << endl;
        }
    }
};

void almostSorted(vector<int> arr) {
    AlmostSortedSolver solver;
    solver.solve(move(arr));
}

int main()
{
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split(rtrim(arr_temp_temp));

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    almostSorted(arr);

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
