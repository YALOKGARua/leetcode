#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <algorithm>
#include <memory>

using namespace std;

class DependencyConstraint {
private:
    int predecessor;
    int successor;
    
public:
    DependencyConstraint(int pred, int succ) : predecessor(pred), successor(succ) {}
    
    int getPredecessor() const { return predecessor; }
    int getSuccessor() const { return successor; }
};

class ConstraintParser {
public:
    static DependencyConstraint parseConstraint(const string& constraintStr) {
        size_t separatorPos = constraintStr.find('<');
        
        if (separatorPos == string::npos) {
            throw invalid_argument("Invalid constraint format");
        }
        
        string predStr = constraintStr.substr(0, separatorPos);
        string succStr = constraintStr.substr(separatorPos + 1);
        
        int predecessor = stoi(predStr);
        int successor = stoi(succStr);
        
        return DependencyConstraint(predecessor, successor);
    }
};

class DependencyGraph {
private:
    int processCount;
    unordered_map<int, unordered_set<int>> adjacencyList;
    unordered_map<int, int> incomingEdges;
    
    void initializeIncomingEdges() {
        for (int process = 1; process <= processCount; process++) {
            incomingEdges[process] = 0;
        }
    }
    
public:
    DependencyGraph(int n) : processCount(n) {
        initializeIncomingEdges();
    }
    
    void addConstraint(const DependencyConstraint& constraint) {
        int pred = constraint.getPredecessor();
        int succ = constraint.getSuccessor();
        
        if (adjacencyList[pred].find(succ) == adjacencyList[pred].end()) {
            adjacencyList[pred].insert(succ);
            incomingEdges[succ]++;
        }
    }
    
    const unordered_set<int>& getSuccessors(int process) const {
        static const unordered_set<int> emptySet;
        auto it = adjacencyList.find(process);
        return (it != adjacencyList.end()) ? it->second : emptySet;
    }
    
    int getIncomingEdgeCount(int process) const {
        auto it = incomingEdges.find(process);
        return (it != incomingEdges.end()) ? it->second : 0;
    }
    
    void decrementIncomingEdges(int process) {
        incomingEdges[process]--;
    }
    
    int getProcessCount() const { return processCount; }
};

class TopologicalSorter {
private:
    using ProcessQueue = priority_queue<int, vector<int>, greater<int>>;
    
    ProcessQueue initializeQueue(const DependencyGraph& graph) {
        ProcessQueue readyProcesses;
        
        for (int process = 1; process <= graph.getProcessCount(); process++) {
            if (graph.getIncomingEdgeCount(process) == 0) {
                readyProcesses.push(process);
            }
        }
        
        return readyProcesses;
    }
    
public:
    vector<int> performTopologicalSort(DependencyGraph& graph) {
        vector<int> sortedOrder;
        ProcessQueue readyProcesses = initializeQueue(graph);
        
        while (!readyProcesses.empty()) {
            int currentProcess = readyProcesses.top();
            readyProcesses.pop();
            
            sortedOrder.push_back(currentProcess);
            
            for (int successor : graph.getSuccessors(currentProcess)) {
                graph.decrementIncomingEdges(successor);
                
                if (graph.getIncomingEdgeCount(successor) == 0) {
                    readyProcesses.push(successor);
                }
            }
        }
        
        return sortedOrder;
    }
};

class ProductionPipelineAnalyzer {
private:
    unique_ptr<DependencyGraph> dependencyGraph;
    TopologicalSorter sorter;
    
public:
    ProductionPipelineAnalyzer(int processCount) 
        : dependencyGraph(make_unique<DependencyGraph>(processCount)) {}
    
    void addProcessConstraint(const DependencyConstraint& constraint) {
        dependencyGraph->addConstraint(constraint);
    }
    
    vector<int> computeValidProcessingOrder() {
        vector<int> sortedOrder = sorter.performTopologicalSort(*dependencyGraph);
        
        if (static_cast<int>(sortedOrder.size()) != dependencyGraph->getProcessCount()) {
            return {};
        }
        
        return sortedOrder;
    }
};

class InputProcessor {
public:
    static vector<DependencyConstraint> readConstraints(int constraintCount) {
        vector<DependencyConstraint> constraints;
        constraints.reserve(constraintCount);
        
        for (int i = 0; i < constraintCount; i++) {
            string constraintStr;
            getline(cin, constraintStr);
            
            DependencyConstraint constraint = ConstraintParser::parseConstraint(constraintStr);
            constraints.push_back(constraint);
        }
        
        return constraints;
    }
};

class OutputFormatter {
public:
    static void displayProcessingOrder(const vector<int>& processingOrder) {
        if (processingOrder.empty()) {
            cout << "INVALID" << endl;
            return;
        }
        
        for (size_t i = 0; i < processingOrder.size(); i++) {
            if (i > 0) cout << " ";
            cout << processingOrder[i];
        }
        cout << endl;
    }
};

class ProductionPipelineApplication {
private:
    unique_ptr<ProductionPipelineAnalyzer> analyzer;
    
public:
    void run() {
        int processCount;
        cin >> processCount;
        cin.ignore();
        
        int constraintCount;
        cin >> constraintCount;
        cin.ignore();
        
        analyzer = make_unique<ProductionPipelineAnalyzer>(processCount);
        
        vector<DependencyConstraint> constraints = InputProcessor::readConstraints(constraintCount);
        
        for (const DependencyConstraint& constraint : constraints) {
            analyzer->addProcessConstraint(constraint);
        }
        
        vector<int> processingOrder = analyzer->computeValidProcessingOrder();
        OutputFormatter::displayProcessingOrder(processingOrder);
    }
};

int main() {
    ProductionPipelineApplication app;
    app.run();
    
    return 0;
}
