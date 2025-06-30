#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <climits>

using namespace std;

int n, l, e;
vector<vector<int>> graph;
unordered_set<int> gateways;

pair<int, int> findShortestPath(int start) {
    vector<int> dist(n, -1);
    vector<int> parent(n, -1);
    queue<int> q;
    
    dist[start] = 0;
    q.push(start);
    
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        
        if (gateways.count(current) && current != start) {
            int node = current;
            while (parent[node] != -1) {
                int prev = parent[node];
                if (gateways.count(node)) {
                    return {prev, node};
                }
                node = prev;
            }
        }
        
        for (int neighbor : graph[current]) {
            if (dist[neighbor] == -1) {
                dist[neighbor] = dist[current] + 1;
                parent[neighbor] = current;
                q.push(neighbor);
            }
        }
    }
    
    return {-1, -1};
}

pair<int, int> selectLinkToSever(int agentPos) {
    for (int neighbor : graph[agentPos]) {
        if (gateways.count(neighbor)) {
            return {agentPos, neighbor};
        }
    }
    
    vector<pair<int, int>> mostDangerousLinks;
    int maxDanger = 0;
    
    for (int i = 0; i < n; i++) {
        int gatewayCount = 0;
        vector<pair<int, int>> nodeLinks;
        
        for (int neighbor : graph[i]) {
            if (gateways.count(neighbor)) {
                gatewayCount++;
                nodeLinks.push_back({i, neighbor});
            }
        }
        
        if (gatewayCount > maxDanger) {
            maxDanger = gatewayCount;
            mostDangerousLinks = nodeLinks;
        }
    }
    
    if (!mostDangerousLinks.empty()) {
        return mostDangerousLinks[0];
    }
    
    for (int neighbor : graph[agentPos]) {
        for (int gateway : graph[neighbor]) {
            if (gateways.count(gateway)) {
                return {neighbor, gateway};
            }
        }
    }
    
    vector<pair<int, int>> criticalLinks;
    for (int i = 0; i < n; i++) {
        int gatewayCount = 0;
        for (int neighbor : graph[i]) {
            if (gateways.count(neighbor)) {
                gatewayCount++;
                criticalLinks.push_back({i, neighbor});
            }
        }
        
        if (gatewayCount >= 2) {
            return criticalLinks.back();
        }
    }
    
    pair<int, int> pathResult = findShortestPath(agentPos);
    if (pathResult.first != -1) {
        return pathResult;
    }
    
    if (!criticalLinks.empty()) {
        return criticalLinks[0];
    }
    
    if (!graph[agentPos].empty()) {
        return {agentPos, graph[agentPos][0]};
    }
    
    return {0, 1};
}

int main() {
    cin >> n >> l >> e;
    cin.ignore();
    
    graph.assign(n, vector<int>());
    
    for (int i = 0; i < l; i++) {
        int n1, n2;
        cin >> n1 >> n2;
        cin.ignore();
        graph[n1].push_back(n2);
        graph[n2].push_back(n1);
    }
    
    for (int i = 0; i < e; i++) {
        int ei;
        cin >> ei;
        cin.ignore();
        gateways.insert(ei);
    }
    
    while (true) {
        int si;
        cin >> si;
        cin.ignore();
        
        pair<int, int> result = selectLinkToSever(si);
        
        if (result.first != -1 && result.second != -1) {
            auto it1 = find(graph[result.first].begin(), graph[result.first].end(), result.second);
            if (it1 != graph[result.first].end()) {
                graph[result.first].erase(it1);
            }
            
            auto it2 = find(graph[result.second].begin(), graph[result.second].end(), result.first);
            if (it2 != graph[result.second].end()) {
                graph[result.second].erase(it2);
            }
        }
        
        cout << result.first << " " << result.second << endl;
    }
    
    return 0;
}
