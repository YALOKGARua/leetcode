#include <stdlib.h>
long long* maximumSegmentSum(int* nums, int n, int* q, int m, int* rs) {
    int* p = calloc(n, 4), *sz = calloc(n, 4), *on = calloc(n, 4);
    long long* sum = calloc(n, 8), *ans = malloc(m * 8), mx = 0;
    for(int i = 0; i < n; ++i) p[i] = i, sz[i] = 1;
    int f(int x) { return p[x] == x ? x : (p[x] = f(p[x])); }
    for(int i = m - 1; i >= 0; --i) {
        ans[i] = mx;
        int x = q[i];
        on[x] = 1;
        sum[x] = nums[x];
        if(x && on[x - 1]) {
            int a = f(x - 1), b = f(x);
            if(a != b) { p[b] = a; sum[a] += sum[b]; sz[a] += sz[b]; }
        }
        if(x + 1 < n && on[x + 1]) {
            int a = f(x + 1), b = f(x);
            if(a != b) { p[b] = a; sum[a] += sum[b]; sz[a] += sz[b]; }
        }
        mx = mx > sum[f(x)] ? mx : sum[f(x)];
    }
    *rs = m;
    free(p); free(sz); free(on); free(sum);
    return ans;
} 