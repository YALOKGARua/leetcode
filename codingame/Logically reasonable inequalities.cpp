#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <algorithm>

using namespace std;

enum class NodeState {
    WHITE,
    GRAY,
    BLACK
};

class InequalityGraph {
private:
    unordered_map<char, unordered_set<char>> adjacencyList;
    unordered_map<char, NodeState> nodeStates;
    unordered_set<char> vertices;

    bool detectCycleRecursive(char current) {
        nodeStates[current] = NodeState::GRAY;
        
        for (char neighbor : adjacencyList[current]) {
            if (nodeStates[neighbor] == NodeState::GRAY) {
                return true;
            }
            
            if (nodeStates[neighbor] == NodeState::WHITE && detectCycleRecursive(neighbor)) {
                return true;
            }
        }
        
        nodeStates[current] = NodeState::BLACK;
        return false;
    }

public:
    void addInequality(char greater, char lesser) {
        vertices.insert(greater);
        vertices.insert(lesser);
        adjacencyList[greater].insert(lesser);
        
        if (nodeStates.find(greater) == nodeStates.end()) {
            nodeStates[greater] = NodeState::WHITE;
        }
        if (nodeStates.find(lesser) == nodeStates.end()) {
            nodeStates[lesser] = NodeState::WHITE;
        }
    }

    bool hasCycle() {
        for (char vertex : vertices) {
            nodeStates[vertex] = NodeState::WHITE;
        }
        
        for (char vertex : vertices) {
            if (nodeStates[vertex] == NodeState::WHITE) {
                if (detectCycleRecursive(vertex)) {
                    return true;
                }
            }
        }
        
        return false;
    }
};

class InequalityParser {
private:
    static pair<char, char> parseInequality(const string& inequality) {
        stringstream ss(inequality);
        string token;
        vector<string> tokens;
        
        while (ss >> token) {
            tokens.push_back(token);
        }
        
        if (tokens.size() >= 3 && tokens[1] == ">") {
            return {tokens[0][0], tokens[2][0]};
        }
        
        return {'\0', '\0'};
    }

public:
    static InequalityGraph buildGraph(const vector<string>& inequalities) {
        InequalityGraph graph;
        
        for (const string& inequality : inequalities) {
            auto [greater, lesser] = parseInequality(inequality);
            if (greater != '\0' && lesser != '\0') {
                graph.addInequality(greater, lesser);
            }
        }
        
        return graph;
    }
};

class ConsistencyChecker {
public:
    static string checkConsistency(const vector<string>& inequalities) {
        InequalityGraph graph = InequalityParser::buildGraph(inequalities);
        return graph.hasCycle() ? "contradiction" : "consistent";
    }
};

int main() {
    int n;
    cin >> n;
    cin.ignore();
    
    vector<string> inequalities;
    inequalities.reserve(n);
    
    for (int i = 0; i < n; i++) {
        string inequality;
        getline(cin, inequality);
        inequalities.push_back(inequality);
    }
    
    cout << ConsistencyChecker::checkConsistency(inequalities) << endl;
    
    return 0;
}
