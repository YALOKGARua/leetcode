#include <stdlib.h>
#define N 1005
#define B ((N+31)/32)
unsigned anc[N][B];
int* g[N], gc[N], deg[N];
int** getAncestors(int n, int** e, int es, int* ec, int* rs, int** rcs) {
    for(int i=0;i<n;i++) gc[i]=0, deg[i]=0;
    for(int i=0;i<es;i++) deg[e[i][1]]++, gc[e[i][0]]++;
    for(int i=0;i<n;i++) g[i]=(int*)malloc(gc[i]*sizeof(int)), gc[i]=0;
    for(int i=0;i<es;i++) g[e[i][0]][gc[e[i][0]]++]=e[i][1];
    for(int i=0;i<n;i++) for(int j=0;j<B;j++) anc[i][j]=0;
    int q[N], l=0, r=0;
    for(int i=0;i<n;i++) if(!deg[i]) q[r++]=i;
    while(l<r){
        int u=q[l++];
        for(int j=0;j<gc[u];j++){
            int v=g[u][j];
            for(int b=0;b<B;b++) anc[v][b]|=anc[u][b];
            anc[v][u/32]|=1u<<(u%32);
            if(--deg[v]==0) q[r++]=v;
        }
    }
    int** res=(int**)malloc(n*sizeof(int*));
    *rcs=(int*)malloc(n*sizeof(int));
    for(int i=0;i<n;i++){
        int sz=0, tmp[N];
        for(int b=0;b<B;b++) for(int k=0;k<32;k++) if(anc[i][b]&(1u<<k)) tmp[sz++]=b*32+k;
        for(int j=0;j<sz-1;j++) for(int k=j+1;k<sz;k++) if(tmp[j]>tmp[k]){int t=tmp[j];tmp[j]=tmp[k];tmp[k]=t;}
        res[i]=(int*)malloc(sz*sizeof(int));
        for(int j=0;j<sz;j++) res[i][j]=tmp[j];
        (*rcs)[i]=sz;
        free(g[i]);
    }
    *rs=n;
    return res;
} 