#include <stdlib.h>
int unequalTriplets(int* nums, int n) {
    int cnt[1001] = {0}, uniq[100], m = 0, i, j, k;
    for(i = 0; i < n; ++i) if(++cnt[nums[i]] == 1) uniq[m++] = nums[i];
    int res = 0;
    for(i = 0; i < m; ++i)
        for(j = i + 1; j < m; ++j)
            for(k = j + 1; k < m; ++k)
                res += cnt[uniq[i]] * cnt[uniq[j]] * cnt[uniq[k]];
    return res;
} 