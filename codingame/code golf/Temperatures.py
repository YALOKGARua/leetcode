n=int(input() or 0)
a=0;b=10**9
s=input().split() if n else []
for i in range(min(n,len(s))):
 t=int(s[i]);u=abs(t)
 if u<b or u==b and t>a:b=u;a=t
print(a if b<10**9 else 0)