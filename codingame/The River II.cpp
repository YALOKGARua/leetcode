#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

class DigitalRiverAnalyzer {
private:
    static constexpr int MAX_DIGIT_SUM = 9 * 6;
    
    static int calculateDigitSum(int number) {
        int sum = 0;
        while (number > 0) {
            sum += number % 10;
            number /= 10;
        }
        return sum;
    }
    
public:
    static int getNextRiverValue(int current) {
        return current + calculateDigitSum(current);
    }
    
private:
    
    static vector<int> findPossiblePredecessors(int target) {
        vector<int> predecessors;
        
        int searchStart = max(1, target - MAX_DIGIT_SUM);
        int searchEnd = target - 1;
        
        for (int candidate = searchStart; candidate <= searchEnd; candidate++) {
            if (getNextRiverValue(candidate) == target) {
                predecessors.push_back(candidate);
            }
        }
        
        return predecessors;
    }
    
public:
    static bool canBeMeetingPoint(int targetNumber) {
        vector<int> predecessors = findPossiblePredecessors(targetNumber);
        return !predecessors.empty();
    }
    
    static vector<int> getAllPredecessors(int targetNumber) {
        return findPossiblePredecessors(targetNumber);
    }
};

class RiverMeetingDetector {
private:
    DigitalRiverAnalyzer analyzer;
    
public:
    bool detectMeetingPoint(int number) {
        return analyzer.canBeMeetingPoint(number);
    }
    
    vector<int> findMeetingRivers(int number) {
        return analyzer.getAllPredecessors(number);
    }
};

class InputProcessor {
public:
    static int readTargetNumber() {
        int number;
        cin >> number;
        return number;
    }
};

class OutputFormatter {
public:
    static void displayMeetingResult(bool isMeetingPoint) {
        cout << (isMeetingPoint ? "YES" : "NO") << endl;
    }
    
    static void displayDetailedAnalysis(int target, const vector<int>& predecessors) {
        cout << "Target: " << target << endl;
        cout << "Predecessors: ";
        for (size_t i = 0; i < predecessors.size(); i++) {
            if (i > 0) cout << ", ";
            cout << predecessors[i];
        }
        cout << endl;
        cout << "Meeting point: " << (!predecessors.empty() ? "YES" : "NO") << endl;
    }
};

class RiverAnalysisApplication {
private:
    RiverMeetingDetector detector;
    
public:
    void run() {
        int targetNumber = InputProcessor::readTargetNumber();
        bool isMeetingPoint = detector.detectMeetingPoint(targetNumber);
        OutputFormatter::displayMeetingResult(isMeetingPoint);
    }
    
    void runDetailedAnalysis() {
        int targetNumber = InputProcessor::readTargetNumber();
        vector<int> predecessors = detector.findMeetingRivers(targetNumber);
        OutputFormatter::displayDetailedAnalysis(targetNumber, predecessors);
    }
};

class DigitalRiverUtils {
public:
    static vector<int> generateRiverSequence(int start, int length) {
        vector<int> sequence;
        sequence.reserve(length);
        
        int current = start;
        for (int i = 0; i < length; i++) {
            sequence.push_back(current);
            current = DigitalRiverAnalyzer::getNextRiverValue(current);
        }
        
        return sequence;
    }
    
    static int findMeetingPoint(int river1Start, int river2Start, int maxSteps = 1000) {
        unordered_set<int> river1Values;
        
        int current1 = river1Start;
        for (int i = 0; i < maxSteps; i++) {
            river1Values.insert(current1);
            current1 = DigitalRiverAnalyzer::getNextRiverValue(current1);
        }
        
        int current2 = river2Start;
        for (int i = 0; i < maxSteps; i++) {
            if (river1Values.count(current2)) {
                return current2;
            }
            current2 = DigitalRiverAnalyzer::getNextRiverValue(current2);
        }
        
        return -1;
    }
    
private:
    static int getNextRiverValue(int current) {
        return DigitalRiverAnalyzer::getNextRiverValue(current);
    }
};

int main() {
    RiverAnalysisApplication app;
    app.run();
    
    return 0;
}
