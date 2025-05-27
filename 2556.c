#include <stdbool.h>
#define MOD 3
int dp[1002][1002];
bool isPossibleToCutPath(int** g, int m, int* c) {
    int n=c[0];
    for(int z=0;z<2;z++){
        for(int i=0;i<m;i++)for(int j=0;j<n;j++)dp[i][j]=0;
        dp[0][0]=1;
        for(int i=0;i<m;i++)for(int j=0;j<n;j++)if(g[i][j]){
            if(i) dp[i][j]=(dp[i][j]+dp[i-1][j])%MOD;
            if(j) dp[i][j]=(dp[i][j]+dp[i][j-1])%MOD;
        }else dp[i][j]=0;
        if(dp[m-1][n-1]<2) return 1;
        g[0][0]=0;
    }
    return 0;
} 