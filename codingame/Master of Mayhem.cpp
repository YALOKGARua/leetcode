#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <memory>
#include <functional>
#include <sstream>
#include <regex>
#include <optional>

using namespace std;

enum class AttributeType {
    HAT, NECKWEAR, COMPANION, CATCHPHRASE, WORD
};

struct AttributeValue {
    string value;
    bool is_partial;
    
    AttributeValue(const string& v = "", bool partial = false) : value(v), is_partial(partial) {}
    
    bool matches(const AttributeValue& other) const {
        if (is_partial) {
            return other.value.find(value) != string::npos;
        }
        return value == other.value;
    }
};

class Entity {
protected:
    string name;
    unordered_map<AttributeType, AttributeValue> attributes;
    
public:
    Entity(const string& n) : name(n) {}
    
    virtual ~Entity() = default;
    
    void setAttribute(AttributeType type, const AttributeValue& value) {
        attributes[type] = value;
    }
    
    optional<AttributeValue> getAttribute(AttributeType type) const {
        auto it = attributes.find(type);
        return it != attributes.end() ? optional<AttributeValue>(it->second) : nullopt;
    }
    
    const string& getName() const { return name; }
    
    bool hasAttribute(AttributeType type) const {
        return attributes.find(type) != attributes.end();
    }
    
    template<typename Func>
    void forEachAttribute(Func&& func) const {
        for (const auto& [type, value] : attributes) {
            func(type, value);
        }
    }
};

class Cyborg : public Entity {
public:
    Cyborg(const string& name) : Entity(name) {}
    
    bool couldBeMayhem(const Entity& mayhem) const {
        bool isCandidate = true;
        mayhem.forEachAttribute([&](AttributeType type, const AttributeValue& mayhemValue) {
            if (type == AttributeType::WORD) {
                auto myCatchphrase = getAttribute(AttributeType::CATCHPHRASE);
                if (myCatchphrase && myCatchphrase->value.find(mayhemValue.value) == string::npos) {
                    isCandidate = false;
                }
            } else {
                auto myValue = getAttribute(type);
                if (myValue && myValue->value != mayhemValue.value) {
                    isCandidate = false;
                }
            }
        });
        return isCandidate;
    }
};

class MayhemMaster : public Entity {
public:
    MayhemMaster() : Entity("Mayhem") {}
    
    bool appliesToCyborg(const Cyborg& cyborg) const {
        auto mayhemHat = getAttribute(AttributeType::HAT);
        if (mayhemHat && mayhemHat->value == "FEDORA") {
            auto cyborgHat = cyborg.getAttribute(AttributeType::HAT);
            if (cyborgHat && cyborgHat->value == "BEANIE") {
                return false;
            }
        }
        return true;
    }
};

class ReportParser {
private:
    regex reportPattern;
    unordered_map<string, AttributeType> attributeMap;
    
public:
    ReportParser() : reportPattern(R"((\w+)'s\s+(\w+)\s+is\s+(?:a\s+|an\s+)?(.*))") {
        attributeMap["hat"] = AttributeType::HAT;
        attributeMap["neckwear"] = AttributeType::NECKWEAR;
        attributeMap["companion"] = AttributeType::COMPANION;
        attributeMap["catchphrase"] = AttributeType::CATCHPHRASE;
        attributeMap["word"] = AttributeType::WORD;
    }
    
    optional<tuple<string, AttributeType, AttributeValue>> parse(const string& report) const {
        smatch match;
        if (regex_match(report, match, reportPattern)) {
            string entityName = match[1].str();
            string attrName = match[2].str();
            string attrValue = match[3].str();
            
            if (attrValue.length() >= 2 && attrValue.front() == '"' && attrValue.back() == '"') {
                attrValue = attrValue.substr(1, attrValue.length() - 2);
            }
            
            auto it = attributeMap.find(attrName);
            if (it != attributeMap.end()) {
                bool isPartial = (it->second == AttributeType::WORD);
                return make_tuple(entityName, it->second, AttributeValue(attrValue, isPartial));
            }
        }
        return nullopt;
    }
};

class MayhemDetective {
private:
    vector<unique_ptr<Cyborg>> cyborgs;
    unique_ptr<MayhemMaster> mayhem;
    unique_ptr<ReportParser> parser;
    
    void processCyborgReports(const vector<string>& reports) {
        for (const auto& report : reports) {
            auto parsed = parser->parse(report);
            if (parsed) {
                auto [name, type, value] = *parsed;
                auto cyborg = find_if(cyborgs.begin(), cyborgs.end(),
                    [&name](const unique_ptr<Cyborg>& c) { return c->getName() == name; });
                if (cyborg != cyborgs.end()) {
                    (*cyborg)->setAttribute(type, value);
                }
            }
        }
    }
    
    void processMayhemReports(const vector<string>& reports) {
        for (const auto& report : reports) {
            auto parsed = parser->parse(report);
            if (parsed) {
                auto [name, type, value] = *parsed;
                if (name == "Mayhem") {
                    mayhem->setAttribute(type, value);
                }
            }
        }
    }
    
    vector<string> findViableCandidates() const {
        vector<string> candidates;
        
        for (const auto& cyborg : cyborgs) {
            if (cyborg->couldBeMayhem(*mayhem) && mayhem->appliesToCyborg(*cyborg)) {
                candidates.push_back(cyborg->getName());
            }
        }
        
        return candidates;
    }
    
public:
    MayhemDetective() : mayhem(make_unique<MayhemMaster>()), parser(make_unique<ReportParser>()) {}
    
    void addCyborg(const string& name) {
        cyborgs.push_back(make_unique<Cyborg>(name));
    }
    
    void processReports(const vector<string>& mayhemReports, const vector<string>& cyborgReports) {
        processMayhemReports(mayhemReports);
        processCyborgReports(cyborgReports);
    }
    
    string investigate() const {
        auto candidates = findViableCandidates();
        
        if (candidates.empty()) {
            return "MISSING";
        } else if (candidates.size() == 1) {
            return candidates[0];
        } else {
            return "INDETERMINATE";
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    MayhemDetective detective;
    
    int cyborg_count;
    cin >> cyborg_count;
    cin.ignore();
    
    for (int i = 0; i < cyborg_count; i++) {
        string cyborg_name;
        cin >> cyborg_name;
        cin.ignore();
        detective.addCyborg(cyborg_name);
    }
    
    int mayhem_report_count;
    cin >> mayhem_report_count;
    cin.ignore();
    
    vector<string> mayhemReports;
    for (int i = 0; i < mayhem_report_count; i++) {
        string mayhem_report;
        getline(cin, mayhem_report);
        mayhemReports.push_back(mayhem_report);
    }
    
    int cyborg_report_count;
    cin >> cyborg_report_count;
    cin.ignore();
    
    vector<string> cyborgReports;
    for (int i = 0; i < cyborg_report_count; i++) {
        string cyborg_report;
        getline(cin, cyborg_report);
        cyborgReports.push_back(cyborg_report);
    }
    
    detective.processReports(mayhemReports, cyborgReports);
    
    cout << detective.investigate() << endl;
    
    return 0;
}
