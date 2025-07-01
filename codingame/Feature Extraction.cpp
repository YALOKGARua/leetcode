#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

template<typename T>
class Matrix {
private:
    vector<vector<T>> data;
    int rows;
    int cols;
    
public:
    Matrix(int r, int c) : rows(r), cols(c) {
        data.assign(rows, vector<T>(cols, T{}));
    }
    
    Matrix(const vector<vector<T>>& input) : data(input), rows(input.size()), cols(input[0].size()) {}
    
    T& operator()(int row, int col) {
        return data[row][col];
    }
    
    const T& operator()(int row, int col) const {
        return data[row][col];
    }
    
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    
    bool isValidPosition(int row, int col) const {
        return row >= 0 && row < rows && col >= 0 && col < cols;
    }
    
    Matrix<T> getSubMatrix(int startRow, int startCol, int subRows, int subCols) const {
        Matrix<T> subMatrix(subRows, subCols);
        
        for (int i = 0; i < subRows; i++) {
            for (int j = 0; j < subCols; j++) {
                if (isValidPosition(startRow + i, startCol + j)) {
                    subMatrix(i, j) = data[startRow + i][startCol + j];
                }
            }
        }
        
        return subMatrix;
    }
    
    void display(const string& separator = " ") const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (j > 0) cout << separator;
                cout << data[i][j];
            }
            cout << endl;
        }
    }
};

class ConvolutionKernel {
private:
    Matrix<int> weights;
    
public:
    ConvolutionKernel(int rows, int cols) : weights(rows, cols) {}
    
    ConvolutionKernel(const Matrix<int>& kernelWeights) : weights(kernelWeights) {}
    
    int& operator()(int row, int col) {
        return weights(row, col);
    }
    
    const int& operator()(int row, int col) const {
        return weights(row, col);
    }
    
    int getRows() const { return weights.getRows(); }
    int getCols() const { return weights.getCols(); }
    
    int computeConvolution(const Matrix<int>& imageRegion) const {
        int convolutionSum = 0;
        
        for (int i = 0; i < getRows(); i++) {
            for (int j = 0; j < getCols(); j++) {
                convolutionSum += imageRegion(i, j) * weights(i, j);
            }
        }
        
        return convolutionSum;
    }
};

class ConvolutionProcessor {
private:
    Matrix<int> inputImage;
    ConvolutionKernel kernel;
    
    Matrix<int> computeOutputDimensions() const {
        int outputRows = inputImage.getRows() - kernel.getRows() + 1;
        int outputCols = inputImage.getCols() - kernel.getCols() + 1;
        return Matrix<int>(outputRows, outputCols);
    }
    
public:
    ConvolutionProcessor(const Matrix<int>& image, const ConvolutionKernel& convKernel) 
        : inputImage(image), kernel(convKernel) {}
    
    Matrix<int> performConvolution() const {
        Matrix<int> outputImage = computeOutputDimensions();
        
        for (int outputRow = 0; outputRow < outputImage.getRows(); outputRow++) {
            for (int outputCol = 0; outputCol < outputImage.getCols(); outputCol++) {
                Matrix<int> imageRegion = inputImage.getSubMatrix(
                    outputRow, outputCol, kernel.getRows(), kernel.getCols()
                );
                
                int convolutionResult = kernel.computeConvolution(imageRegion);
                outputImage(outputRow, outputCol) = convolutionResult;
            }
        }
        
        return outputImage;
    }
    
    void validateInputs() const {
        if (kernel.getRows() > inputImage.getRows() || 
            kernel.getCols() > inputImage.getCols()) {
            throw invalid_argument("Kernel dimensions exceed image dimensions");
        }
    }
};

class InputProcessor {
public:
    static Matrix<int> readImageMatrix() {
        int rows, cols;
        cin >> rows >> cols;
        
        Matrix<int> image(rows, cols);
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cin >> image(i, j);
            }
        }
        
        return image;
    }
    
    static ConvolutionKernel readKernelMatrix() {
        int rows, cols;
        cin >> rows >> cols;
        
        ConvolutionKernel kernel(rows, cols);
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cin >> kernel(i, j);
            }
        }
        
        return kernel;
    }
};

class OutputFormatter {
public:
    static void displayConvolutionResult(const Matrix<int>& result) {
        result.display(" ");
    }
    
    static void displayErrorMessage(const string& error) {
        cerr << "Error: " << error << endl;
    }
};

class FeatureExtractionApplication {
private:
    Matrix<int> inputImage;
    ConvolutionKernel kernel;
    
public:
    FeatureExtractionApplication() 
        : inputImage(1, 1), kernel(1, 1) {}
    
    void run() {
        try {
            inputImage = InputProcessor::readImageMatrix();
            kernel = InputProcessor::readKernelMatrix();
            
            ConvolutionProcessor processor(inputImage, kernel);
            processor.validateInputs();
            
            Matrix<int> convolutionResult = processor.performConvolution();
            OutputFormatter::displayConvolutionResult(convolutionResult);
            
        } catch (const exception& e) {
            OutputFormatter::displayErrorMessage(e.what());
        }
    }
};

class ConvolutionAnalyzer {
public:
    static void analyzeConvolutionParameters(const Matrix<int>& image, const ConvolutionKernel& kernel) {
        cout << "Input Image Dimensions: " << image.getRows() << "x" << image.getCols() << endl;
        cout << "Kernel Dimensions: " << kernel.getRows() << "x" << kernel.getCols() << endl;
        
        int outputRows = image.getRows() - kernel.getRows() + 1;
        int outputCols = image.getCols() - kernel.getCols() + 1;
        cout << "Output Dimensions: " << outputRows << "x" << outputCols << endl;
    }
    
    static int calculateTotalOperations(const Matrix<int>& image, const ConvolutionKernel& kernel) {
        int outputRows = image.getRows() - kernel.getRows() + 1;
        int outputCols = image.getCols() - kernel.getCols() + 1;
        int operationsPerPosition = kernel.getRows() * kernel.getCols();
        
        return outputRows * outputCols * operationsPerPosition;
    }
};

int main() {
    FeatureExtractionApplication app;
    app.run();
    
    return 0;
}
