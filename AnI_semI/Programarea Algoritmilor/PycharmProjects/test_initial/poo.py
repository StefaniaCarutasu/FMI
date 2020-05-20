n=int(input())
L=[]
for i in range(n):
    x=int(input())
    L.append(x)
i=0
j=n-1
while i<j:
    while L[i]%2==1:
        i+=1
    while L[j]%2==0:
        j-=1
    L[i],L[j]=L[j],L[i]
    i+=1
    j-=1
print(L)