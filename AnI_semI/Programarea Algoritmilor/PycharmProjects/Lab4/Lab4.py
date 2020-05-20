"""
#Problema 1-Triplete pitagoreice

def ipotenuza(a, b):
    c=(a*a+b*b)**(1/2)
    return c
b=int(input())
f=open("triplete_pitagoreice.txt","w")
a=1; contor=0
while a<b:
    c=ipotenuza(a,b)
    d=int(c)
    if d==c:
        f.write("("+str(a)+','+str(b)+","+str(d)+")")
        contor+=1
    a+=1
if contor==0:
    print("Nu s-au gasit numere sa verifice relatia")

#Problema 2- lungime cerc/ arie disc
import math
def lungime_arie_cerc(r):
    pi=math.pi
    return pi*r*r, 2*pi*r
r=int(input())
print(lungime_arie_cerc(r))

#Problema 4-Generator infinit nr prime

def generator(j,i):
    if i!=0:
        prim=1
        k=2
        while k<=j//2 and prim==1:
            if j%k==0:
                prim=0
            k+=1
        if prim==1:
            print(j)
            return(generator(j+1,i-1))
        else:
            return(generator(j+1,i))
    else:
        return(i)

n=int(input())
generator(2,n)
"""
import heapq as HQ
L=[2,5,7,9,6,10,8,12,3,1]
HQ.heapify(L)
print(L)
HQ.heappush(L,3)
print(L)
HQ.heappush(L,3)
print(L)
print(HQ.heappop(L))
print(L)

