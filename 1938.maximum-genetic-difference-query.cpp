class Solution {
private:
    struct TrieNode {
        TrieNode* children[2];
        int count;
        TrieNode() {
            children[0] = children[1] = nullptr;
            count = 0;
        }
    };
    
    void insert(TrieNode* root, int num) {
        TrieNode* curr = root;
        for (int i = 20; i >= 0; --i) {
            int bit = (num >> i) & 1;
            if (!curr->children[bit]) {
                curr->children[bit] = new TrieNode();
            }
            curr->count++;
            curr = curr->children[bit];
        }
        curr->count++;
    }
    
    void remove(TrieNode* root, int num) {
        TrieNode* curr = root;
        for (int i = 20; i >= 0; --i) {
            int bit = (num >> i) & 1;
            curr->count--;
            curr = curr->children[bit];
        }
        curr->count--;
    }
    
    int findMaxXOR(TrieNode* root, int num) {
        TrieNode* curr = root;
        int result = 0;
        for (int i = 20; i >= 0; --i) {
            int bit = (num >> i) & 1;
            int target = 1 - bit;
            if (curr->children[target] && curr->children[target]->count > 0) {
                result |= (1 << i);
                curr = curr->children[target];
            } else {
                curr = curr->children[bit];
            }
        }
        return result;
    }

public:
    vector<int> maxGeneticDifference(vector<int>& parents, vector<vector<int>>& queries) {
        int n = parents.size();
        vector<vector<int>> children(n);
        int root = -1;
        for (int i = 0; i < n; ++i) {
            if (parents[i] == -1) {
                root = i;
            } else {
                children[parents[i]].push_back(i);
            }
        }
        vector<vector<pair<int, int>>> nodeQueries(n);
        for (int i = 0; i < queries.size(); ++i) {
            nodeQueries[queries[i][0]].push_back({queries[i][1], i});
        }
        vector<int> result(queries.size());
        TrieNode* trie = new TrieNode();
        function<void(int)> dfs = [&](int node) {
            insert(trie, node);
            for (auto& [val, idx] : nodeQueries[node]) {
                result[idx] = findMaxXOR(trie, val);
            }
            for (int child : children[node]) {
                dfs(child);
            }
            remove(trie, node);
        };
        dfs(root);
        return result;
    }
}; 