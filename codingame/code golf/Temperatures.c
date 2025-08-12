#include <stdio.h>
#include <stdlib.h>
int main(){int n,a=0,b=1e9,t;scanf("%d",&n);for(int i=0;i<n&&scanf("%d",&t);i++){int x=abs(t);if(x<b||x==b&&t>a){b=x;a=t;}}printf("%d",b<1000000000?a:0);}