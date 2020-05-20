def citire(n,v):
    n=int(input())
    v=[int(x) for x in range(n)]
    return n,v
def afisare(v):
    for i in v:
        print(i," ")
def valpoz(v):
    poz=[]
    for i in v:
        if i%2==0:
            poz.append(i)
    return poz
def semn(v):
    for i in range(len(v)):
        v[i]=-v[i]
    return v
