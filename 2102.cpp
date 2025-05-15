#include <set>
#include <string>
using namespace std;

class SORTracker {
    set<pair<int, string>> left;
    set<pair<int, string>> right;
    int k = 0;
public:
    SORTracker() {}
    
    void add(string name, int score) {
        auto p = make_pair(-score, name);
        if (left.size() < k) {
            left.insert(p);
        } else if (left.empty() || p <= *left.rbegin()) {
            left.insert(p);
        } else {
            right.insert(p);
        }
        
        while (left.size() > k) {
            right.insert(*left.rbegin());
            left.erase(prev(left.end()));
        }
        while (left.size() < k && !right.empty()) {
            left.insert(*right.begin());
            right.erase(right.begin());
        }
    }
    
    string get() {
        k++;
        if (!right.empty()) {
            left.insert(*right.begin());
            right.erase(right.begin());
        }
        return left.rbegin()->second;
    }
}; 