#include <vector>
using namespace std;

class FenwickTree {
private:
    vector<int> tree;
    int n;
    
    int lowbit(int x) {
        return x & (-x);
    }
    
public:
    FenwickTree(int size) {
        n = size;
        tree.resize(n + 1, 0);
    }
    
    void update(int i, int val) {
        while (i <= n) {
            tree[i] += val;
            i += lowbit(i);
        }
    }
    
    int query(int i) {
        int sum = 0;
        while (i > 0) {
            sum += tree[i];
            i -= lowbit(i);
        }
        return sum;
    }
};

class Solution {
public:
    long long goodTriplets(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        vector<int> pos2(n);
        for (int i = 0; i < n; i++) {
            pos2[nums2[i]] = i;
        }
        
        vector<int> pos1(n);
        for (int i = 0; i < n; i++) {
            pos1[i] = pos2[nums1[i]];
        }
        
        FenwickTree left(n), right(n);
        for (int i = 0; i < n; i++) {
            right.update(pos1[i] + 1, 1);
        }
        
        long long result = 0;
        for (int i = 0; i < n; i++) {
            right.update(pos1[i] + 1, -1);
            int leftCount = left.query(pos1[i]);
            int rightCount = right.query(n) - right.query(pos1[i] + 1);
            result += (long long)leftCount * rightCount;
            left.update(pos1[i] + 1, 1);
        }
        
        return result;
    }
}; 