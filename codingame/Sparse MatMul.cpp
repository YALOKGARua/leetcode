#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <iomanip>
#include <cmath>
#include <sstream>

using namespace std;

struct SparseMatrix {
    map<pair<int, int>, double> elements;
    int rows, cols;
    
    SparseMatrix(int r, int c) : rows(r), cols(c) {}
    
    void set(int row, int col, double value) {
        if (value != 0.0) {
            elements[{row, col}] = value;
        }
    }
    
    double get(int row, int col) const {
        auto it = elements.find({row, col});
        return (it != elements.end()) ? it->second : 0.0;
    }
};

SparseMatrix multiply(const SparseMatrix& A, const SparseMatrix& B) {
    SparseMatrix result(A.rows, B.cols);
    
    for (const auto& aElement : A.elements) {
        int i = aElement.first.first;
        int k = aElement.first.second;
        double aValue = aElement.second;
        
        for (const auto& bElement : B.elements) {
            int k2 = bElement.first.first;
            int j = bElement.first.second;
            double bValue = bElement.second;
            
            if (k == k2) {
                double product = aValue * bValue;
                double currentValue = result.get(i, j);
                double newValue = currentValue + product;
                
                if (newValue != 0.0) {
                    result.set(i, j, newValue);
                } else if (currentValue != 0.0) {
                    result.elements.erase({i, j});
                }
            }
        }
    }
    
    return result;
}

int main() {
    int m, n, p;
    cin >> m >> n >> p;
    cin.ignore();
    
    int countA, countB;
    cin >> countA >> countB;
    cin.ignore();
    
    SparseMatrix A(m, n);
    for (int i = 0; i < countA; i++) {
        int row, column;
        double value;
        cin >> row >> column >> value;
        cin.ignore();
        A.set(row, column, value);
    }
    
    SparseMatrix B(n, p);
    for (int i = 0; i < countB; i++) {
        int row, column;
        double value;
        cin >> row >> column >> value;
        cin.ignore();
        B.set(row, column, value);
    }
    
    SparseMatrix result = multiply(A, B);
    
    vector<tuple<int, int, double>> outputElements;
    for (const auto& element : result.elements) {
        outputElements.push_back({
            element.first.first,
            element.first.second,
            element.second
        });
    }
    
    sort(outputElements.begin(), outputElements.end());
    
    for (const auto& element : outputElements) {
        double value = get<2>(element);
        cout << get<0>(element) << " " << get<1>(element) << " ";
        
        if (abs(value - round(value)) < 1e-9) {
            cout << fixed << setprecision(1) << value << endl;
        } else {
            ostringstream oss;
            oss << fixed << setprecision(10) << value;
            string str = oss.str();
            
            str.erase(str.find_last_not_of('0') + 1, string::npos);
            if (str.back() == '.') str.pop_back();
            
            cout << str << endl;
        }
    }
    
    return 0;
}
