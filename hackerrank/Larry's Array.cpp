#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

template<typename T>
class InversionCalculator {
private:
    vector<T> workspace;
    
public:
    long long calculateMergeSort(vector<T>& arr, int left, int right) {
        if (left >= right) return 0;
        
        int mid = left + (right - left) / 2;
        long long inv_count = 0;
        
        inv_count += calculateMergeSort(arr, left, mid);
        inv_count += calculateMergeSort(arr, mid + 1, right);
        inv_count += merge(arr, left, mid, right);
        
        return inv_count;
    }
    
private:
    long long merge(vector<T>& arr, int left, int mid, int right) {
        workspace.resize(right - left + 1);
        
        int i = left, j = mid + 1, k = 0;
        long long inv_count = 0;
        
        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) {
                workspace[k++] = arr[i++];
            } else {
                workspace[k++] = arr[j++];
                inv_count += (mid - i + 1);
            }
        }
        
        while (i <= mid) workspace[k++] = arr[i++];
        while (j <= right) workspace[k++] = arr[j++];
        
        for (int idx = 0; idx < k; idx++) {
            arr[left + idx] = workspace[idx];
        }
        
        return inv_count;
    }
};

class PermutationSortabilityAnalyzer {
private:
    InversionCalculator<int> calc;
    
public:
    static constexpr int ROTATION_SIZE = 3;
    
    struct AnalysisResult {
        bool sortable;
        long long inversionCount;
        string reasoning;
        
        AnalysisResult(bool s, long long ic, const string& r) 
            : sortable(s), inversionCount(ic), reasoning(r) {}
    };
    
    AnalysisResult analyzePermutation(vector<int> permutation) {
        long long inversions = calc.calculateMergeSort(permutation, 0, permutation.size() - 1);
        
        bool canSort = (inversions % 2 == 0);
        string reason = canSort ? "Even inversion parity allows sorting" 
                                : "Odd inversion parity prevents sorting";
        
        return AnalysisResult(canSort, inversions, reason);
    }
};

class AlternativeInversionCounter {
public:
    static long long countInversionsQuadratic(const vector<int>& arr) {
        long long count = 0;
        int n = arr.size();
        
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                if (arr[i] > arr[j]) {
                    count++;
                }
            }
        }
        
        return count;
    }
};

class LarrysArraySolver {
private:
    PermutationSortabilityAnalyzer analyzer;
    
    static bool validatePermutation(const vector<int>& arr) {
        vector<bool> seen(arr.size() + 1, false);
        
        for (int val : arr) {
            if (val < 1 || val > arr.size() || seen[val]) {
                return false;
            }
            seen[val] = true;
        }
        
        return true;
    }
    
public:
    string solve(vector<int> array) {
        if (!validatePermutation(array)) {
            return "NO";
        }
        
        auto result = analyzer.analyzePermutation(array);
        return result.sortable ? "YES" : "NO";
    }
    
    static string solveAlternative(vector<int> array) {
        long long inversions = AlternativeInversionCounter::countInversionsQuadratic(array);
        return (inversions % 2 == 0) ? "YES" : "NO";
    }
};

string larrysArray(vector<int> A) {
    LarrysArraySolver solver;
    return solver.solve(move(A));
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string n_temp;
        getline(cin, n_temp);

        int n = stoi(ltrim(rtrim(n_temp)));

        string A_temp_temp;
        getline(cin, A_temp_temp);

        vector<string> A_temp = split(rtrim(A_temp_temp));

        vector<int> A(n);

        for (int i = 0; i < n; i++) {
            int A_item = stoi(A_temp[i]);

            A[i] = A_item;
        }

        string result = larrysArray(A);

        fout << result << "\n";
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
