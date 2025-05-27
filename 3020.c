#include <stdint.h>
#include <string.h>
#define M 100001
int cmp(const void*a,const void*b){return*(int*)a-*(int*)b;}
int maximumLength(int* a, int n) {
    int cnt[M] = {0}, res = 1;
    for(int i = 0; i < n; ++i) cnt[a[i]]++;
    for(int i = 1; i < M; ++i) {
        if(!cnt[i]) continue;
        int x = i, len = 0, odd = 0, c = 0;
        while(x < M && cnt[x]) {
            if(cnt[x] > 1) odd = 1;
            ++c;
            x *= 2;
        }
        if(c == 1) len = 1;
        else if(odd) len = c * 2 - 1;
        else len = c;
        if(len > res) res = len;
    }
    return res;
} 