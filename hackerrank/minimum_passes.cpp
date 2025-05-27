#include <bits/stdc++.h>
using namespace std;
long minimumPasses(long m, long w, long p, long n) {
    using ll = unsigned long long;
    ll res=LLONG_MAX, pass=0, c=0;
    while(c<(ll)n) {
        if((ll)m*(ll)w>=(ll)n-c) return pass+1;
        res=min(res,pass+((ll)n-c+((ll)m*w)-1)/((ll)m*w));
        if(c<p) {
            ll need=(p-c+((ll)m*w)-1)/((ll)m*w);
            pass+=need; c+=need*(ll)m*w;
            if(c<(ll)n) continue;
        }
        ll buy=c/p; c%=p;
        ll total=m+w+buy;
        m=total/2; w=total-m;
        pass++; c+=(ll)m*w;
    }
    return min(res,pass);
}
int main() {
    ios::sync_with_stdio(0);cin.tie(0);
    long m,w,p,n; cin>>m>>w>>p>>n;
    cout<<minimumPasses(m,w,p,n)<<'\n';
} 