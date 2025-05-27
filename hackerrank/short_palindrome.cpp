#include <bits/stdc++.h>
using namespace std;
int shortPalindrome(string s) {
    int mod=1e9+7, res=0;
    vector<long long> pre(26), pre2(26*26);
    for(char ch:s) {
        int x=ch-'a';
        for(int y=0;y<26;++y) res=(res+pre2[y*26+x])%mod;
        for(int y=0;y<26;++y) pre2[x*26+y]=(pre2[x*26+y]+pre[y])%mod;
        pre[x]++;
    }
    return res;
}
int main() {
    ios::sync_with_stdio(0);cin.tie(0);
    string s;
    getline(cin, s);
    cout << shortPalindrome(s) << '\n';
} 