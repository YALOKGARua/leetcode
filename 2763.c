#include <string.h>
int sumImbalanceNumbers(int* a, int n) {
    int res=0, vis[1002];
    for(int i=0;i<n;i++){
        memset(vis,0,sizeof(vis));
        vis[a[i]]=1;int cnt=0;
        for(int j=i+1;j<n;j++){
            if(!vis[a[j]]){
                if(!vis[a[j]-1]&&!vis[a[j]+1]) cnt++;
                if(vis[a[j]-1]&&vis[a[j]+1]) cnt--;
            }
            vis[a[j]]=1;
            res+=cnt;
        }
    }
    return res;
} 