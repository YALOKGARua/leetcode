#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Operation {
    string type;
    int operand;
};

int main() {
    string expression;
    getline(cin, expression);
    
    istringstream iss(expression);
    vector<string> tokens;
    string token;
    
    while (iss >> token) {
        tokens.push_back(token);
    }
    
    vector<Operation> operations;
    
    int firstNumber = stoi(tokens[0]);
    operations.push_back({"ADD", firstNumber});
    
    for (int i = 1; i + 1 < tokens.size(); i += 2) {
        string operatorStr = tokens[i];
        int value = stoi(tokens[i + 1]);
        
        string opType = (operatorStr == "+") ? "ADD" : "SUB";
        operations.push_back({opType, value});
    }
    
    vector<Operation> compressedOps;
    vector<int> counts;
    
    for (int i = 0; i < operations.size(); ) {
        Operation currentOp = operations[i];
        int count = 1;
        
        while (i + count < operations.size() && 
               operations[i + count].type == currentOp.type && 
               operations[i + count].operand == currentOp.operand) {
            count++;
        }
        
        compressedOps.push_back(currentOp);
        counts.push_back(count);
        i += count;
    }
    
    for (int i = 0; i < compressedOps.size(); i++) {
        if (counts[i] > 1) {
            cout << "REPEAT " << counts[i] << endl;
        }
        cout << compressedOps[i].type << " cgx " << compressedOps[i].operand << endl;
    }
    
    cout << "EXIT" << endl;
    
    return 0;
}