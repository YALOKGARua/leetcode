#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <algorithm>
#include <memory>

using namespace std;

enum class ConnectionType {
    SERIES,
    PARALLEL
};

class SwitchState {
private:
    unordered_set<string> activeSwitches;
    
public:
    void toggleSwitch(const string& switchName) {
        if (activeSwitches.count(switchName)) {
            activeSwitches.erase(switchName);
        } else {
            activeSwitches.insert(switchName);
        }
    }
    
    bool isSwitchActive(const string& switchName) const {
        return activeSwitches.count(switchName) > 0;
    }
    
    void reset() {
        activeSwitches.clear();
    }
};

struct CircuitSegment {
    ConnectionType type;
    vector<string> switches;
    
    CircuitSegment(ConnectionType t) : type(t) {}
    
    bool evaluate(const SwitchState& switchState) const {
        if (switches.empty()) return true;
        
        if (type == ConnectionType::SERIES) {
            for (const string& sw : switches) {
                if (!switchState.isSwitchActive(sw)) {
                    return false;
                }
            }
            return true;
        } else {
            for (const string& sw : switches) {
                if (switchState.isSwitchActive(sw)) {
                    return true;
                }
            }
            return false;
        }
    }
};

class CircuitExpression {
private:
    vector<CircuitSegment> segments;
    string equipmentName;
    
public:
    CircuitExpression(const string& name) : equipmentName(name) {}
    
    void addSegment(const CircuitSegment& segment) {
        segments.push_back(segment);
    }
    
    bool evaluate(const SwitchState& switchState) const {
        for (const CircuitSegment& segment : segments) {
            if (!segment.evaluate(switchState)) {
                return false;
            }
        }
        return true;
    }
    
    const string& getEquipmentName() const {
        return equipmentName;
    }
};

class WiringParser {
private:
    static vector<string> tokenize(const string& line) {
        istringstream iss(line);
        vector<string> tokens;
        string token;
        
        while (iss >> token) {
            tokens.push_back(token);
        }
        
        return tokens;
    }
    
    static CircuitSegment createSegment(ConnectionType type, const vector<string>& switchNames) {
        CircuitSegment segment(type);
        segment.switches = switchNames;
        return segment;
    }
    
public:
    static unique_ptr<CircuitExpression> parseWiring(const string& wiringDescription) {
        vector<string> tokens = tokenize(wiringDescription);
        
        if (tokens.empty()) {
            return nullptr;
        }
        
        string equipmentName = tokens[0];
        auto expression = make_unique<CircuitExpression>(equipmentName);
        
        ConnectionType currentType = ConnectionType::SERIES;
        vector<string> currentGroup;
        
        for (size_t i = 1; i < tokens.size(); i++) {
            const string& token = tokens[i];
            
            if (token == "=") {
                if (!currentGroup.empty()) {
                    expression->addSegment(createSegment(currentType, currentGroup));
                    currentGroup.clear();
                }
                currentType = ConnectionType::PARALLEL;
            } else if (token == "-") {
                if (!currentGroup.empty()) {
                    expression->addSegment(createSegment(currentType, currentGroup));
                    currentGroup.clear();
                }
                currentType = ConnectionType::SERIES;
            } else {
                currentGroup.push_back(token);
            }
        }
        
        if (!currentGroup.empty()) {
            expression->addSegment(createSegment(currentType, currentGroup));
        }
        
        return expression;
    }
};

class ElectricalSystem {
private:
    vector<unique_ptr<CircuitExpression>> circuits;
    SwitchState switchState;
    
public:
    void addCircuit(const string& wiringDescription) {
        auto circuit = WiringParser::parseWiring(wiringDescription);
        if (circuit) {
            circuits.push_back(move(circuit));
        }
    }
    
    void toggleSwitch(const string& switchName) {
        switchState.toggleSwitch(switchName);
    }
    
    void resetAllSwitches() {
        switchState.reset();
    }
    
    vector<pair<string, bool>> evaluateAllCircuits() const {
        vector<pair<string, bool>> results;
        results.reserve(circuits.size());
        
        for (const auto& circuit : circuits) {
            bool isOn = circuit->evaluate(switchState);
            results.emplace_back(circuit->getEquipmentName(), isOn);
        }
        
        return results;
    }
};

class InputProcessor {
public:
    static vector<string> readWiringDescriptions(int count) {
        vector<string> descriptions;
        descriptions.reserve(count);
        
        for (int i = 0; i < count; i++) {
            string line;
            getline(cin, line);
            descriptions.push_back(line);
        }
        
        return descriptions;
    }
    
    static vector<string> readSwitchToggles(int count) {
        vector<string> toggles;
        toggles.reserve(count);
        
        for (int i = 0; i < count; i++) {
            string switchName;
            getline(cin, switchName);
            toggles.push_back(switchName);
        }
        
        return toggles;
    }
};

class OutputFormatter {
public:
    static void displayResults(const vector<pair<string, bool>>& results) {
        for (const auto& [equipmentName, isOn] : results) {
            cout << equipmentName << " is " << (isOn ? "ON" : "OFF") << endl;
        }
    }
};

class ElectricalSystemSimulator {
private:
    ElectricalSystem system;
    
public:
    void setupCircuits(const vector<string>& wiringDescriptions) {
        system.resetAllSwitches();
        
        for (const string& description : wiringDescriptions) {
            system.addCircuit(description);
        }
    }
    
    void applySwitchToggles(const vector<string>& toggles) {
        for (const string& switchName : toggles) {
            system.toggleSwitch(switchName);
        }
    }
    
    vector<pair<string, bool>> getSystemState() const {
        return system.evaluateAllCircuits();
    }
};

class ElectricalApprenticeApplication {
private:
    ElectricalSystemSimulator simulator;
    
public:
    void run() {
        int circuitCount;
        cin >> circuitCount;
        cin.ignore();
        
        vector<string> wiringDescriptions = InputProcessor::readWiringDescriptions(circuitCount);
        
        int toggleCount;
        cin >> toggleCount;
        cin.ignore();
        
        vector<string> switchToggles = InputProcessor::readSwitchToggles(toggleCount);
        
        simulator.setupCircuits(wiringDescriptions);
        simulator.applySwitchToggles(switchToggles);
        
        vector<pair<string, bool>> results = simulator.getSystemState();
        OutputFormatter::displayResults(results);
    }
};

int main() {
    ElectricalApprenticeApplication app;
    app.run();
    
    return 0;
}
