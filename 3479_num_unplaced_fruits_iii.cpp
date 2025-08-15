#include <vector>
#include <algorithm>

using std::vector;

class Solution {
public:
	int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
		int n = (int)baskets.size();
		if (n == 0) return (int)fruits.size();
		seg.assign(4 * n, 0);
		build(1, 0, n - 1, baskets);
		int unplaced = 0;
		for (int x : fruits) {
			if (seg[1] < x) {
				++unplaced;
				continue;
			}
			int idx = findFirstAtLeast(1, 0, n - 1, x);
			updateToZero(1, 0, n - 1, idx);
		}
		return unplaced;
	}

private:
	vector<int> seg;
	void build(int node, int l, int r, const vector<int>& a) {
		if (l == r) { seg[node] = a[l]; return; }
		int m = (l + r) >> 1;
		build(node << 1, l, m, a);
		build(node << 1 | 1, m + 1, r, a);
		seg[node] = std::max(seg[node << 1], seg[node << 1 | 1]);
	}
	int findFirstAtLeast(int node, int l, int r, int x) {
		if (seg[node] < x) return -1;
		if (l == r) return l;
		int m = (l + r) >> 1;
		int left = findFirstAtLeast(node << 1, l, m, x);
		if (left != -1) return left;
		return findFirstAtLeast(node << 1 | 1, m + 1, r, x);
	}
	void updateToZero(int node, int l, int r, int pos) {
		if (l == r) { seg[node] = 0; return; }
		int m = (l + r) >> 1;
		if (pos <= m) updateToZero(node << 1, l, m, pos);
		else updateToZero(node << 1 | 1, m + 1, r, pos);
		seg[node] = std::max(seg[node << 1], seg[node << 1 | 1]);
	}
};