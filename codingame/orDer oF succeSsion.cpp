#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include <sstream>

using namespace std;

enum class Gender {
    MALE,
    FEMALE
};

enum class Religion {
    ANGLICAN,
    CATHOLIC,
    OTHER
};

class Person {
private:
    string name;
    string parentName;
    int birthYear;
    bool isDead;
    Religion religion;
    Gender gender;
    vector<shared_ptr<Person>> children;
    
public:
    Person(const string& n, const string& p, int birth, bool dead, Religion rel, Gender gen)
        : name(n), parentName(p), birthYear(birth), isDead(dead), religion(rel), gender(gen) {}
    
    const string& getName() const { return name; }
    const string& getParentName() const { return parentName; }
    int getBirthYear() const { return birthYear; }
    bool getIsDead() const { return isDead; }
    Religion getReligion() const { return religion; }
    Gender getGender() const { return gender; }
    
    void addChild(shared_ptr<Person> child) {
        children.push_back(child);
    }
    
    const vector<shared_ptr<Person>>& getChildren() const {
        return children;
    }
    
    bool isEligibleForThrone() const {
        return !isDead && religion != Religion::CATHOLIC;
    }
};

class PersonFactory {
public:
    static shared_ptr<Person> createPerson(const string& line) {
        istringstream iss(line);
        string name, parent, death, religion, genderStr;
        int birth;
        
        iss >> name >> parent >> birth >> death >> religion >> genderStr;
        
        bool isDead = (death != "-");
        
        Religion rel = Religion::OTHER;
        if (religion == "Anglican") rel = Religion::ANGLICAN;
        else if (religion == "Catholic") rel = Religion::CATHOLIC;
        
        Gender gender = (genderStr == "M") ? Gender::MALE : Gender::FEMALE;
        
        return make_shared<Person>(name, parent, birth, isDead, rel, gender);
    }
};

class SuccessionComparator {
public:
    bool operator()(const shared_ptr<Person>& a, const shared_ptr<Person>& b) const {
        if (a->getGender() != b->getGender()) {
            return a->getGender() == Gender::MALE;
        }
        return a->getBirthYear() < b->getBirthYear();
    }
};

class FamilyTree {
private:
    unordered_map<string, shared_ptr<Person>> personMap;
    shared_ptr<Person> monarch;
    
    void buildRelationships() {
        for (const auto& [name, person] : personMap) {
            const string& parentName = person->getParentName();
            if (parentName != "-") {
                auto parentIt = personMap.find(parentName);
                if (parentIt != personMap.end()) {
                    parentIt->second->addChild(person);
                }
            } else {
                monarch = person;
            }
        }
        
        sortAllChildren();
    }
    
    void sortAllChildren() {
        SuccessionComparator comparator;
        for (auto& [name, person] : personMap) {
            vector<shared_ptr<Person>>& children = const_cast<vector<shared_ptr<Person>>&>(person->getChildren());
            sort(children.begin(), children.end(), comparator);
        }
    }
    
public:
    void addPerson(shared_ptr<Person> person) {
        personMap[person->getName()] = person;
    }
    
    void constructTree() {
        buildRelationships();
    }
    
    shared_ptr<Person> getMonarch() const {
        return monarch;
    }
};

class SuccessionCalculator {
private:
    vector<string> successionOrder;
    
    void traverseSuccession(shared_ptr<Person> person) {
        if (person->isEligibleForThrone()) {
            successionOrder.push_back(person->getName());
        }
        
        for (const auto& child : person->getChildren()) {
            traverseSuccession(child);
        }
    }
    
public:
    vector<string> calculateSuccession(const FamilyTree& familyTree) {
        successionOrder.clear();
        
        shared_ptr<Person> monarch = familyTree.getMonarch();
        if (monarch) {
            traverseSuccession(monarch);
        }
        
        return successionOrder;
    }
};

class SuccessionService {
private:
    FamilyTree familyTree;
    SuccessionCalculator calculator;
    
public:
    void processPeopleData(const vector<string>& peopleData) {
        for (const string& personData : peopleData) {
            shared_ptr<Person> person = PersonFactory::createPerson(personData);
            familyTree.addPerson(person);
        }
        
        familyTree.constructTree();
    }
    
    vector<string> computeSuccessionOrder() {
        return calculator.calculateSuccession(familyTree);
    }
};

class InputProcessor {
public:
    static vector<string> readPeopleData(int n) {
        vector<string> peopleData;
        peopleData.reserve(n);
        
        for (int i = 0; i < n; i++) {
            string line;
            getline(cin, line);
            peopleData.push_back(line);
        }
        
        return peopleData;
    }
};

class OutputFormatter {
public:
    static void displaySuccessionOrder(const vector<string>& successionOrder) {
        for (const string& name : successionOrder) {
            cout << name << endl;
        }
    }
};

int main() {
    int n;
    cin >> n;
    cin.ignore();
    
    vector<string> peopleData = InputProcessor::readPeopleData(n);
    
    SuccessionService service;
    service.processPeopleData(peopleData);
    
    vector<string> successionOrder = service.computeSuccessionOrder();
    
    OutputFormatter::displaySuccessionOrder(successionOrder);
    
    return 0;
}
