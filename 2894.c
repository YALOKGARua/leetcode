int differenceOfSums(int n, int m){
    int t=n/m;
    int s=n*(n+1)/2;
    int d=m*t*(t+1)/2;
    return s-2*d;
} 