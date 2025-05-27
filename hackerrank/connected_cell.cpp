#include <bits/stdc++.h>
using namespace std;
int n, m, mx;
vector<vector<int>> a, v;
int dx[]{-1,-1,-1,0,0,1,1,1}, dy[]{-1,0,1,-1,1,-1,0,1};
int dfs(int x, int y) {
    if (x<0||y<0||x>=n||y>=m||!a[x][y]||v[x][y]) return 0;
    v[x][y]=1; int s=1;
    for(int d=0;d<8;++d) s+=dfs(x+dx[d],y+dy[d]);
    return s;
}
int main() {
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m; a=v=vector<vector<int>>(n,vector<int>(m));
    for(auto& r:a) for(auto& x:r) cin>>x;
    for(int i=0;i<n;++i) for(int j=0;j<m;++j) if(a[i][j]&&!v[i][j]) mx=max(mx,dfs(i,j));
    cout<<mx;
} 