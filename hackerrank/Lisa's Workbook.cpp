#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

class WorkbookAnalyzer {
private:
    struct PageLayout {
        int pageNumber;
        int firstProblemIndex;
        int lastProblemIndex;
        
        bool containsSpecialProblem() const {
            return pageNumber >= firstProblemIndex && pageNumber <= lastProblemIndex;
        }
    };
    
    static vector<PageLayout> generateChapterPageLayout(int chapterProblems, int maxProblemsPerPage, int startingPageNumber) {
        vector<PageLayout> pageLayouts;
        int currentPageNumber = startingPageNumber;
        int problemsProcessed = 0;
        
        while (problemsProcessed < chapterProblems) {
            int remainingProblems = chapterProblems - problemsProcessed;
            int problemsOnCurrentPage = min(maxProblemsPerPage, remainingProblems);
            
            PageLayout layout;
            layout.pageNumber = currentPageNumber;
            layout.firstProblemIndex = problemsProcessed + 1;
            layout.lastProblemIndex = problemsProcessed + problemsOnCurrentPage;
            
            pageLayouts.emplace_back(layout);
            
            problemsProcessed += problemsOnCurrentPage;
            currentPageNumber++;
        }
        
        return pageLayouts;
    }
    
public:
    static int countSpecialProblemsInWorkbook(int totalChapters, int maxProblemsPerPage, const vector<int>& chapterProblemCounts) {
        int specialProblemCount = 0;
        int currentPageNumber = 1;
        
        for (int chapterIndex = 0; chapterIndex < totalChapters; ++chapterIndex) {
            int problemsInCurrentChapter = chapterProblemCounts[chapterIndex];
            
            auto chapterPageLayouts = generateChapterPageLayout(
                problemsInCurrentChapter, 
                maxProblemsPerPage, 
                currentPageNumber
            );
            
            for (const auto& pageLayout : chapterPageLayouts) {
                if (pageLayout.containsSpecialProblem()) {
                    specialProblemCount++;
                }
            }
            
            currentPageNumber += chapterPageLayouts.size();
        }
        
        return specialProblemCount;
    }
};

int workbook(int n, int k, vector<int> arr) {
    return WorkbookAnalyzer::countSpecialProblemsInWorkbook(n, k, arr);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int k = stoi(first_multiple_input[1]);

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split(rtrim(arr_temp_temp));

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    int result = workbook(n, k, arr);

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
