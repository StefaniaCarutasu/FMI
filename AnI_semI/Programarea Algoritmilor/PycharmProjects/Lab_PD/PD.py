"""
#Problema dominouri- subsir crescator de lungime maxima
f=open("date.in", "r")
n=int(f.readline())
V=[]
for i in range(n):
    i=f.readline()
    i=i.split()
    i[0]=int(i[0])
    i[1]=int(i[1])
    V.append(i)
L=[1]*n
m=1
for i in range(1,n):
    for j in range(i):
        if V[j][1] == V[i][0] and L[i] <= L[j]+1:
            L[i] = L[j]+1
m = max(L)
a = []
for i in range(n-1, -1, -1):
   if L[i] == m:
       a.append(V[i])
       m -= 1
a.reverse()
print(a)
print(len(a))
print(L.count(len(a)))

#Problema 2- parcurgere matrice + suma max
f=open("date.in", "r")
l=f.readline()
l=l.split()
n=int(l[0])
m=int(l[1])
M=[]
for i in range(n):
    line=f.readline()
    line=line.split()
    for j in range(len(line)):
        line[j]=int(line[j])
    M.append(line)


T=[[0]*m]*n
T[0][0]=M[0][0]
for i in range(0,n):
    for j in range (0,m):
        if i>0 and j>0:
            T[i][j]=M[i][j]+max(T[i-1][j], T[i][j-1])
        elif i>0 and j==0:
            T[i][j] = M[i][j] + T[i - 1][j]
        elif i==0 and j>0:
            T[i][j] = M[i][j] + T[i][j - 1]


print(T[n-1][m-1])

#Problema 4- construire de vector
f=open("date.in", "r")
line=f.readline()
line=line.split()
n=int(line[0])
k=int(line[1])
L=[]
for i in range(n):
    line=f.readline()
    line=line.split()
    for j in range(len(line)):
        line[j]=int(line[j])
    L.append(line)

M=[[0]*(k+1)]*n
for i in range(n):
    for j in range(1,len(L[i])):
        if i == 0:
            M[i][j]=l.index(j)



#Problema 3- distanta Levenshtein
cuv1=input()
cuv2=input()
n=len(cuv1)
m=len(cuv2)
M=[]
for i in range(n+2):
     M.append([])
     for j in range(m+2):
            M[i].append(int('0'))
for i in range(2,n+2):
    M[i][0]=cuv1[i-2]
for i in range(2,m+2):
    M[0][i]=cuv2[i-2]

for i in range(1,n+2):
    for j in range(1,m+2):
        if i == 1 and j == 1:
            if cuv1[0] == cuv2[0]:
                M[1][1]=0
            else: M[1][1]=1
        elif j > 1 and i == 1:
            M[i][j] = M[i][j-1]+1
        elif i > 1 and j == 1:
            M[i][j] = M[i-1][j] + 1
        elif M[i][0] == M[0][j]:
            M[i][j] = M[i-1][j-1]
        else:
            M[i][j] = 1 + min(M[i-1][j-1], M[i][j-1], M[i-1][j])
for i in M:
    print(i)

#Aia cu Ali Moshu
f=open("date.in", "r")
n=int(f.readline())
V=f.readline().split()
for i in range(n):
    V[i]=int(V[i])
Min_jump=[n]*(n+1)
Min_jump[0]=0
jump_path=[n]*(n+1)
jump_path[0]=0
for i in range(1,n+1):
    for j in range(i):
        if i <= j+V[j]:
            Min_jump[i]=min(Min_jump[i], Min_jump[j]+1)
            #if Min_jump[i] == Min_jump[j]+1 and jump_path[i]==0:
            jump_path[i]=min(jump_path[i],j)
d=jump_path[n]
i=n-1
D=[]
D.append(d)
while i > 0:
    if i == d:
        D.append(jump_path[i])
        d=jump_path[i]
    i-=1
print(D)


#nr de moduri in care poti urca o scara
f=open("date.in","r")
n=int(f.readline())
m=int(f.readline())
V=[0]*(n+1)
for i in range(m):
    V[i]=1
for i in range(m,n+1):
    k=1
    while k<=m:
        V[i] += V[i-k]
        k += 1

print(V)
print(max(V))


#Spectacole

f=open("date.in", "r")
n=int(f.readline())
L=[]
P=[]
for i in range(n):
    line=f.readline()
    line=line.split()
    for j in range(len(line)):
        line[j]=int(line[j])
    L.append(line)
    P.append(line[2])
L.sort(key=lambda x: x[1])
for i in range(1, n):
    for j in range(0,i):
        if L[i][0] >= L[j][1]:
            P[i]=max(P[i],L[j][2]+L[i][2])
print(max(P))
i=n-1
m=max(P)
while P[i] != m:
    i-=1
import collections
D=collections.deque()
for j in range(i):
    if L[j][1] <= L[i][0]:
        D.append(j)
D.append(i)
D=list(D)
for i in range(len(D)-1):
    if L[i][1] > L[i+1][0] and D[i]!=-1:
        if P[i]<P[i+1]:
            D[i+1]=-1
        else: D[i]=-1
for i in range(len(D)):
    if D[i] != -1:
        print(D[i])


#Rucsac dinamic
f=open("date.in","r")
n=int(f.readline())
V=[]
for line in f:
    line=line.split()
    line[0]=int(line[0]); line[1]=int(line[1]) #line[0]-greutate is line[1]-profit
    V.append(line)
V.sort(key= lambda x: x[0]) #sort dupa greutate
M=[]
for i in range(len(V)):
     M.append([])
     for j in range(n+1):
            M[i].append(0)
for i in range(len(V)):
    M[i][0]=0
for i in range(1,n+1):
    if V[0][0] <= i:
        M[0][i] = V[0][0]
for i in range(1, len(V)):
    for j in range(1,n+1):
        if V[i][0] <= j:
            M[i][j]=max(M[i-1][j], V[i][1]+M[i-1][j-V[i][0]])
        else:
            M[i][j]=M[i-1][j]

print(M)
#Monede ca Popescu
f=open("date.in", "r")
n=int(f.readline())
M=[int(x) for x in f.readline().split()]
import collections
D=collections.deque(x for x in M)
V=[0]*(n+1)
for i in M:
    V[i]=1
while len(D)>=1:
    x=D[0]
    for i in range(len(M)):
        if M[i] + x <= n:
            if V[M[i]+x] == 0:
                V[M[i]+x] = V[x]+1
                D.append(M[i]+x)
            else:
                V[M[i]+x] = min(V[M[i]+x], V[x]+1 )
    D.popleft()
print(V)

#Sortare topologica
f=open("date.in", "r")
n=int(f.readline())
Gr=[0]*(n+1)
M=[]
V=[0]*(n+1)
import collections
D=collections.deque()
for line in f:
    line=line.split()
    for j in range(len(line)):
        line[j] = int(line[j])
    M.append(line)
    Gr[line[1]] += 1
for i in range(1, n+1):
    if Gr[i] == 0:
        D.append(i)
        V[i]=1
Q=[]
while len(D)>0:
    for i in range(len(M)):
        if M[i][0] == D[0] and V[M[i][1]] == 0:
            D.append(M[i][1])
            V[M[i][1]] = 1
    Q.append(D[0])
    D.popleft()
print(Q)
"""