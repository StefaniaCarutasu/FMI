"""
Problema 1- problema timpului mediu minim
f=open("nume").read().split()
L=[(i+1,int(f[i]))for i in range(len(f))]
def cmp(t):
   return t[1]
round(x,2)-rotunjeste

f=open("alabalaportocala").read().split()
L=[(i+1,int(f[i]))for i in range(len(f))]
def cmp(t):
   return t[1]
def afisare_timpi_servire(V):
    s=0
    i=0
    sum=0
    for x in V:
        s += L[i][1]
        print(i, " ", s, " ", x[1], '\n')
        i+=1
        sum+=s

    print(round(sum/(i),2))
print("Pt lista nesortata", '\n')
afisare_timpi_servire(L)
print("Pt lista sortata crescator",'\n')
L.sort(key=cmp)
afisare_timpi_servire(L)
print("Pt lista sortata descrescator",'\n')
L.sort(key=cmp, reverse=True)
afisare_timpi_servire(L)
"""
'''
Problema 2-problema spectacolelor
#L=[("10:00","11:20","Scufita Rosie"),("09:30","12:10","Punguta cu doi bani"),("08:20","09:50","Vrajitorul din Oz"),("11:30","14:00","Capra cu trei iezi"),("12:10","13:10", "Micul Print"),("14:00","16:00", "Povestea porcului"),("15:00","15:30", "Frumoasa din padurea adormita")]
f=open("alabalaportocala").read().split('\n')
g=open("program_spect.txt","w")

def cmp(t):
    return t[1]
L=[]
for i in range(len(f)):
    t=(f[i][:5],f[i][6:11],f[i][12:])
    L.append(t)
Q=[]
L.sort(key=cmp)
fin="00:00"
i=0
for x in L:
    if L[i][0]>=fin:
        Q.append(x)
        fin=L[i][1]
    i+=1
for t in Q:
   g.write(t[0]+"-"+t[1]+" "+t[2]+'\n')
#Problema 3-turn inaltime max
def functie(k):
    return k[0]

f=open("timpi.txt", "r")
n=int(f.readline())
l=[]
for i in range(n):
    t=f.readline()
    t=t.split(" ")
    t[0]=int(t[0])
    if t[1][len(t[1])-1] == "\n":
         t[1]=t[1][0:len(t[1])-1]
    l.append(tuple(t))
l.sort(key=functie,reverse=True)
l1=[]
j=0
h=0
for i in range(n):
    if i==0:
        l1.append(l[0])
        h+=l[i][0]
    else:
        if l[i][0]<l1[j][0] and l[i][1] != l1[j][1]:
            l1.append(l[i])
            j+=1
            h += l[i][0]
        
print(l1,"\n",h)

#Problema 4- plata cu nr min de bancnote
f=open("bancnote.txt","r")
l=f.readline()
l=l.split()
for i in range(len(l)):
    l[i]=int(l[i])
l.sort(reverse=True)
s=f.readline()
s=int(s)
i=0
suma=str(s)+"="
while s>0:
    k=0
    j=k*l[i]
    while s-j>=0:
        k+=1
        j = k * l[i]
    k-=1
    s-=k*l[i]

    if k>0:
        suma+=str(l[i])+"*"+str(k)+"+"
    i+=1
suma=suma[0:len(suma)-1]
print(suma)

#Problema 5-minimizarea intarzierii maxime
f=open("activitati.txt","r")
n=f.readline()
n=int(n)
l=[]
for i in range(n):
    k=f.readline()
    if k[len(k)-1] is "\n":
        k=k[0:len(k)-1]
    k=k.split(" ")
    k[0]=int(k[0])
    k[1]=int(k[1])
    k=tuple(k)
    l.append(k)
l.sort(key=lambda x: x[1])
T=0
imax=0
g=open("timp.txt","w")
for i in range(n):
    j=0
    t=T+l[i][0]
    if t>l[i][1]:
        j=t-l[i][1]
    g.write(str(T) + "->"+str(t)+" "+"Intarzierea este "+str(j)+"\n")
    T=t
    if j>imax:
        imax=j
g.write(str(imax))
g.close()
print(l)

# Problema 7-Problema rucsacului
f = open("obiecte.txt","r")
n = int(f.readline())
l = []
for i in range(n):
    t = f.readline()
    t = t.split()
    t[0] = int(t[0])
    t[1] = int(t[1])
    t=tuple(t)
    l.append(t)
l.sort(key=lambda x: x[0]/x[1], reverse=True)
G = int(f.readline())
L = []
i=0
while G>=0 and i<len(l):
    if l[i][1]<=G:
        L.append(l[i])
        G -= l[i][1]
    else:
        G = l[i][1] - G
        x = round(float(G/l[i][0]),3)
        t = tuple((l[i][0],x))
        L.append(t)
    i+=1
print(l,"\n")
print(L)
'''
#Problema 8- Planificarea proiectelor cu profit maxim
f = open("proiecte.txt", "r")
l=f.read()
l=l.split("\n")
for i in range(len(l)):
    l[i]=l[i].split(" ")
    l[i][1]=int(l[i][1])
    l[i][2]=int(l[i][2])
    l[i]=tuple(l[i])
l.sort(key = lambda x : x[2], reverse = True)
#print(L)
timp = 0
sol = []
for p in l:
    if p[1] >= timp:
        sol.append(p[0])
        timp += 1
print(sol)