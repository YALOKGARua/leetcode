#include <iostream>
#include <string>
#include <algorithm>
#include <memory>

using namespace std;

class NumberValidator {
public:
    static bool isGrowingNumber(const string& number) {
        if (number.empty()) return false;
        
        for (size_t i = 1; i < number.length(); i++) {
            if (number[i] < number[i - 1]) {
                return false;
            }
        }
        
        return true;
    }
    
    static bool isValidNumberString(const string& number) {
        if (number.empty()) return false;
        
        for (char digit : number) {
            if (digit < '0' || digit > '9') {
                return false;
            }
        }
        
        return true;
    }
};

class StringArithmetic {
public:
    static string incrementByOne(const string& number) {
        string result = number;
        int carry = 1;
        
        for (int i = static_cast<int>(result.length()) - 1; i >= 0 && carry > 0; i--) {
            int digit = (result[i] - '0') + carry;
            result[i] = static_cast<char>('0' + (digit % 10));
            carry = digit / 10;
        }
        
        if (carry > 0) {
            result = "1" + result;
        }
        
        return result;
    }
    
    static string removeLeadingZeros(const string& number) {
        size_t firstNonZero = number.find_first_not_of('0');
        
        if (firstNonZero == string::npos) {
            return "0";
        }
        
        return number.substr(firstNonZero);
    }
};

class GrowingNumberProcessor {
private:
    static string makeGrowingNumber(const string& number) {
        string result = number;
        
        for (size_t i = 1; i < result.length(); i++) {
            if (result[i] < result[i - 1]) {
                char correctionDigit = result[i - 1];
                
                for (size_t j = i; j < result.length(); j++) {
                    result[j] = correctionDigit;
                }
                
                break;
            }
        }
        
        return result;
    }
    
public:
    static string findNextGrowingNumber(const string& inputNumber) {
        string candidate = StringArithmetic::incrementByOne(inputNumber);
        
        if (NumberValidator::isGrowingNumber(candidate)) {
            return candidate;
        }
        
        return makeGrowingNumber(candidate);
    }
};

class GrowingNumberAnalyzer {
private:
    string inputNumber;
    
public:
    GrowingNumberAnalyzer(const string& number) : inputNumber(number) {}
    
    string computeNextGrowingNumber() {
        validateInput();
        return GrowingNumberProcessor::findNextGrowingNumber(inputNumber);
    }
    
private:
    void validateInput() {
        if (!NumberValidator::isValidNumberString(inputNumber)) {
            throw invalid_argument("Invalid number format");
        }
    }
};

class InputProcessor {
public:
    static string readNumberString() {
        string numberStr;
        getline(cin, numberStr);
        return StringArithmetic::removeLeadingZeros(numberStr);
    }
};

class OutputFormatter {
public:
    static void displayResult(const string& result) {
        cout << result << endl;
    }
    
    static void displayError(const string& errorMessage) {
        cerr << "Error: " << errorMessage << endl;
    }
};

class GrowingNumberApplication {
private:
    unique_ptr<GrowingNumberAnalyzer> analyzer;
    
public:
    void run() {
        try {
            string inputNumber = InputProcessor::readNumberString();
            analyzer = make_unique<GrowingNumberAnalyzer>(inputNumber);
            
            string nextGrowingNumber = analyzer->computeNextGrowingNumber();
            OutputFormatter::displayResult(nextGrowingNumber);
            
        } catch (const exception& e) {
            OutputFormatter::displayError(e.what());
        }
    }
};

class GrowingNumberUtils {
public:
    static vector<string> generateGrowingSequence(const string& start, int count) {
        vector<string> sequence;
        sequence.reserve(count);
        
        string current = start;
        for (int i = 0; i < count; i++) {
            current = GrowingNumberProcessor::findNextGrowingNumber(current);
            sequence.push_back(current);
        }
        
        return sequence;
    }
    
    static bool compareNumbers(const string& num1, const string& num2) {
        if (num1.length() != num2.length()) {
            return num1.length() < num2.length();
        }
        
        return num1 < num2;
    }
    
    static string findLargestGrowingNumber(int digits) {
        return string(digits, '9');
    }
    
    static string findSmallestGrowingNumber(int digits) {
        if (digits == 1) return "1";
        return "1" + string(digits - 1, '1');
    }
};

class NumberPatternAnalyzer {
public:
    static int countGrowingNumbers(int digits) {
        if (digits <= 0) return 0;
        if (digits == 1) return 9;
        
        int count = 0;
        for (int firstDigit = 1; firstDigit <= 9; firstDigit++) {
            count += countGrowingNumbersStartingWith(firstDigit, digits - 1);
        }
        
        return count;
    }
    
private:
    static int countGrowingNumbersStartingWith(int startDigit, int remainingDigits) {
        if (remainingDigits == 0) return 1;
        
        int count = 0;
        for (int nextDigit = startDigit; nextDigit <= 9; nextDigit++) {
            count += countGrowingNumbersStartingWith(nextDigit, remainingDigits - 1);
        }
        
        return count;
    }
};

int main() {
    GrowingNumberApplication app;
    app.run();
    
    return 0;
}
