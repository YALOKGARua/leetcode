int longestSubsequence(char* s, int k) {
    int n=0, len=0; for(;s[len];len++) if(s[len]=='0') n++;
    long long v=0, p=1;
    for(int i=len-1;i>=0;i--){
        if(s[i]=='1'){
            v+=p;
            if(v>k) break;
            n++;
        }
        if(p<=k) p<<=1;
    }
    return n;
} 