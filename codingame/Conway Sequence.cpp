#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class ConwaySequenceGenerator {
private:
    vector<int> currentSequence;
    
    vector<int> generateNextSequence(const vector<int>& sequence) {
        vector<int> nextSequence;
        
        if (sequence.empty()) return nextSequence;
        
        int currentElement = sequence[0];
        int count = 1;
        
        for (size_t i = 1; i < sequence.size(); i++) {
            if (sequence[i] == currentElement) {
                count++;
            } else {
                nextSequence.push_back(count);
                nextSequence.push_back(currentElement);
                
                currentElement = sequence[i];
                count = 1;
            }
        }
        
        nextSequence.push_back(count);
        nextSequence.push_back(currentElement);
        
        return nextSequence;
    }
    
public:
    ConwaySequenceGenerator(int initialValue) {
        currentSequence.push_back(initialValue);
    }
    
    vector<int> getSequenceAtLine(int targetLine) {
        vector<int> workingSequence = currentSequence;
        
        for (int line = 1; line < targetLine; line++) {
            workingSequence = generateNextSequence(workingSequence);
        }
        
        return workingSequence;
    }
    
    void printSequence(const vector<int>& sequence) {
        for (size_t i = 0; i < sequence.size(); i++) {
            if (i > 0) cout << " ";
            cout << sequence[i];
        }
        cout << endl;
    }
};

int main() {
    int r, l;
    cin >> r;
    cin >> l;
    
    ConwaySequenceGenerator generator(r);
    vector<int> result = generator.getSequenceAtLine(l);
    generator.printSequence(result);
    
    return 0;
}
