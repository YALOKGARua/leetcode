#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int minStacksNeeded(const string& containers) {
    vector<char> stacks;
    
    for (char container : containers) {
        int bestStack = -1;
        char bestTop = 'Z' + 1;
        
        for (int i = 0; i < stacks.size(); i++) {
            if (stacks[i] >= container && stacks[i] < bestTop) {
                bestStack = i;
                bestTop = stacks[i];
            }
        }
        
        if (bestStack != -1) {
            stacks[bestStack] = container;
        } else {
            stacks.push_back(container);
        }
    }
    
    return stacks.size();
}

int main() {
    int n;
    cin >> n;
    cin.ignore();
    
    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line);
        cout << minStacksNeeded(line) << endl;
    }
    
    return 0;
}
