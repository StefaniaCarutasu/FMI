n=int(input())
Lp=[]
Li=[]
L=[]
for i in range(n):
    x=int(input())
    L.append(x)
for x in L:
    if x%2==0:
        Lp.append(x)
    else:
        Li.append(x)
for x in Lp:
    Li.append(x)
print(Li)
"""
i=0
j=n-1

while i<=j:
    while L[j]%2==0:
        j-=1
    while L[i]%2!=0:
        i+=1
    x=L[i]
    L[i]=L[j]
    L[j]=x
    print(L)
    i+=1
    j-=1
"""
