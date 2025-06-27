#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string program;
    getline(cin, program);
    
    int registerValue = 0;
    int instructionCount = 0;
    bool counting = false;
    int pos = 0;
    
    while (pos < program.length()) {
        if (pos + 2 < program.length() && program.substr(pos, 3) == "/*$") {
            if (counting) instructionCount++;
            pos += 3;
        }
        else if (pos + 2 < program.length() && program.substr(pos, 3) == "/**") {
            int start = pos + 3;
            int end = start;
            while (end < program.length() && program[end] != '/') {
                end++;
            }
            int n = end - start;
            registerValue *= (n + 1);
            if (counting) instructionCount++;
            pos = end + 1;
        }
        else if (pos + 2 < program.length() && program.substr(pos, 3) == "/*/") {
            int start = pos + 3;
            int end = start;
            while (end < program.length() && program[end] != '/') {
                end++;
            }
            int n = end - start;
            registerValue *= (-n);
            if (counting) instructionCount++;
            pos = end + 1;
        }
        else if (pos + 1 < program.length() && program.substr(pos, 2) == "/$") {
            int start = pos + 2;
            int end = start;
            while (end < program.length() && program[end] != '/') {
                end++;
            }
            int n = end - start;
            registerValue += n;
            if (counting) instructionCount++;
            pos = end + 1;
        }
        else if (pos + 1 < program.length() && program.substr(pos, 2) == "//") {
            int start = pos + 2;
            int end = start;
            while (end < program.length() && program[end] != '/') {
                end++;
            }
            int n = end - start;
            registerValue -= n;
            if (counting) instructionCount++;
            pos = end + 1;
        }
        else if (program[pos] == '$') {
            if (!counting) {
                counting = true;
                instructionCount = 0;
            } else {
                registerValue += instructionCount;
                counting = false;
            }
            pos++;
        }
        else {
            pos++;
        }
    }
    
    cout << registerValue << endl;
    
    return 0;
}
