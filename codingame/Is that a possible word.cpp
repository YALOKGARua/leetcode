#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <sstream>

using namespace std;

int main() {
    string inputLine;
    getline(cin, inputLine);
    
    set<char> alphabet;
    stringstream ss(inputLine);
    string token;
    while (ss >> token) {
        alphabet.insert(token[0]);
    }
    
    string statesLine;
    getline(cin, statesLine);
    
    int numberOfTransitions;
    cin >> numberOfTransitions;
    cin.ignore();
    
    map<pair<string, char>, string> transitions;
    
    for (int i = 0; i < numberOfTransitions; i++) {
        string transitionLine;
        getline(cin, transitionLine);
        
        stringstream ts(transitionLine);
        string fromState, toState;
        char symbol;
        
        ts >> fromState >> symbol >> toState;
        transitions[{fromState, symbol}] = toState;
    }
    
    string startState;
    getline(cin, startState);
    
    string endStatesLine;
    getline(cin, endStatesLine);
    
    set<string> endStates;
    stringstream es(endStatesLine);
    while (es >> token) {
        endStates.insert(token);
    }
    
    int numberOfWords;
    cin >> numberOfWords;
    cin.ignore();
    
    for (int i = 0; i < numberOfWords; i++) {
        string word;
        getline(cin, word);
        
        bool valid = true;
        string currentState = startState;
        
        for (char c : word) {
            if (alphabet.find(c) == alphabet.end()) {
                valid = false;
                break;
            }
            
            auto key = make_pair(currentState, c);
            if (transitions.find(key) == transitions.end()) {
                valid = false;
                break;
            }
            
            currentState = transitions[key];
        }
        
        if (valid && endStates.find(currentState) != endStates.end()) {
            cout << "true" << endl;
        } else {
            cout << "false" << endl;
        }
    }
    
    return 0;
}
