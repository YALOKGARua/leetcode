#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

class MatrixLayerRotationProcessor {
private:
    struct LayerBoundaries {
        int topRow, bottomRow, leftCol, rightCol;
        
        LayerBoundaries(int top, int bottom, int left, int right) 
            : topRow(top), bottomRow(bottom), leftCol(left), rightCol(right) {}
    };
    
    static vector<int> extractLayerElementsCounterClockwise(const vector<vector<int>>& matrix, 
                                                           const LayerBoundaries& bounds) {
        vector<int> layerElements;
        
        for (int col = bounds.leftCol; col <= bounds.rightCol; ++col) {
            layerElements.push_back(matrix[bounds.topRow][col]);
        }
        
        for (int row = bounds.topRow + 1; row <= bounds.bottomRow; ++row) {
            layerElements.push_back(matrix[row][bounds.rightCol]);
        }
        
        if (bounds.bottomRow > bounds.topRow) {
            for (int col = bounds.rightCol - 1; col >= bounds.leftCol; --col) {
                layerElements.push_back(matrix[bounds.bottomRow][col]);
            }
        }
        
        if (bounds.rightCol > bounds.leftCol) {
            for (int row = bounds.bottomRow - 1; row > bounds.topRow; --row) {
                layerElements.push_back(matrix[row][bounds.leftCol]);
            }
        }
        
        return layerElements;
    }
    
    static void insertRotatedLayerElements(vector<vector<int>>& matrix, 
                                         const LayerBoundaries& bounds,
                                         const vector<int>& rotatedElements) {
        int elementIndex = 0;
        
        for (int col = bounds.leftCol; col <= bounds.rightCol; ++col) {
            matrix[bounds.topRow][col] = rotatedElements[elementIndex++];
        }
        
        for (int row = bounds.topRow + 1; row <= bounds.bottomRow; ++row) {
            matrix[row][bounds.rightCol] = rotatedElements[elementIndex++];
        }
        
        if (bounds.bottomRow > bounds.topRow) {
            for (int col = bounds.rightCol - 1; col >= bounds.leftCol; --col) {
                matrix[bounds.bottomRow][col] = rotatedElements[elementIndex++];
            }
        }
        
        if (bounds.rightCol > bounds.leftCol) {
            for (int row = bounds.bottomRow - 1; row > bounds.topRow; --row) {
                matrix[row][bounds.leftCol] = rotatedElements[elementIndex++];
            }
        }
    }
    
    static vector<int> performOptimizedRotation(const vector<int>& originalSequence, int rotationSteps) {
        int sequenceLength = originalSequence.size();
        if (sequenceLength == 0) return originalSequence;
        
        int effectiveRotation = rotationSteps % sequenceLength;
        
        vector<int> rotatedSequence(sequenceLength);
        for (int i = 0; i < sequenceLength; ++i) {
            int newPosition = (i - effectiveRotation + sequenceLength) % sequenceLength;
            rotatedSequence[newPosition] = originalSequence[i];
        }
        
        return rotatedSequence;
    }
    
public:
    static void executeMatrixLayerRotation(vector<vector<int>>& matrix, int rotationCount) {
        int matrixHeight = matrix.size();
        int matrixWidth = matrix[0].size();
        int concentricLayerCount = min(matrixHeight, matrixWidth) / 2;
        
        for (int layerIndex = 0; layerIndex < concentricLayerCount; ++layerIndex) {
            LayerBoundaries currentLayerBounds(
                layerIndex, 
                matrixHeight - 1 - layerIndex,
                layerIndex, 
                matrixWidth - 1 - layerIndex
            );
            
            vector<int> extractedLayerElements = extractLayerElementsCounterClockwise(matrix, currentLayerBounds);
            vector<int> rotatedLayerElements = performOptimizedRotation(extractedLayerElements, rotationCount);
            insertRotatedLayerElements(matrix, currentLayerBounds, rotatedLayerElements);
        }
    }
};

class MatrixDisplayUtility {
public:
    static void printMatrix(const vector<vector<int>>& matrix) {
        for (const auto& row : matrix) {
            for (int i = 0; i < row.size(); ++i) {
                cout << row[i];
                if (i < row.size() - 1) cout << " ";
            }
            cout << "\n";
        }
    }
};

void matrixRotation(vector<vector<int>> matrix, int r) {
    MatrixLayerRotationProcessor::executeMatrixLayerRotation(matrix, r);
    MatrixDisplayUtility::printMatrix(matrix);
}

int main()
{
    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int m = stoi(first_multiple_input[0]);

    int n = stoi(first_multiple_input[1]);

    int r = stoi(first_multiple_input[2]);

    vector<vector<int>> matrix(m);

    for (int i = 0; i < m; i++) {
        matrix[i].resize(n);

        string matrix_row_temp_temp;
        getline(cin, matrix_row_temp_temp);

        vector<string> matrix_row_temp = split(rtrim(matrix_row_temp_temp));

        for (int j = 0; j < n; j++) {
            int matrix_row_item = stoi(matrix_row_temp[j]);

            matrix[i][j] = matrix_row_item;
        }
    }

    matrixRotation(matrix, r);

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
