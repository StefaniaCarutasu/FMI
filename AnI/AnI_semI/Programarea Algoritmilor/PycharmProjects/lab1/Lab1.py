"""
Problema 1
a=int(input())
b=int(input())
c=int(input())
d=b*b-4*a*c
if d==0:
    print("x1=x2=",-b/(2*a))
elif d>0:
    print("x1=",(-b+d**(1/2))/2*a, "x2=", (-b-d**(1/2))/2*a)
elif d<0:
    print("Ecuatia nu are solutii reale")


#Problema 2
x=int(input())  #lungimea initiala a sariturii
n=int(input())  #nr de sarituri dupa care se schimba lungimea
p=int(input())  #procentul cu care scade saritura
m=int(input())  #nr total de sarituri
dist=0
if n>m:
    dist=m*x
else:
    while m>0:
        dist+=n*x
        m-=n
        x1=x-(p/100)*x
        x=x1
print(dist)


#Problema 3
l1=int(input())
l2=int(input())
sup=l1*l2

#Problema 4
n=int(input())
L=[None]*n
for i in range(n):
    x=float(input())
    L[i]=x
    max=0
for i in range(n-1):
    if L[i]<L[i+1]:
        k=L[i+1]-L[i]
        if k>max:
            max=k
print(max)
"""
#Problema 5
max1=max2=-10000000
n=int(input())
l=[None]*n
for i in range(n):
    x=int(input())
    l[i]=x
for x in l:
    if x>max1:
        max2=max1
        max1=x
    elif x>max2:
        max2=x
if max1!=max2:
    print(max1, " ", max2)



