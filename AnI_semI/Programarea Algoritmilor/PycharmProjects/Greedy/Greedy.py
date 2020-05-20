"""
#Problema cuielor
f=open("input.txt", "r")
A=[]
for line in f:
    line=line.split()
    line[0]=int(line[0]); line[1]=int(line[1])
    line=tuple(line)
    A.append(line)
A.sort(key=lambda x: x[0])
S=[]; nrc=0; cui=-1
for x in A:
    if x[0]<cui and x[1]>=cui:
        continue
    if x[0]>cui:
        S.append(x[1]); nrc+=1; cui=x[1]
    if x[1]<cui:
        S.poplist()
        S.append(x[1])
        cui=x[1]
print(len(S))


#Planif activ in nr min de sali
f=open("input.txt","r")
A=[]
for line in f:
    line = line.split()
    line[0]=int(line[0])
    line[1]=int(line[1])
    A.append(line)
f.close()
A.sort(key=lambda x: x[0])
S=[]
Q=[]
S.append(A[0])
k=0
Q.insert(0, A[0][1])
for x in A[1:]:
    q=Q.pop(0)
    if x[0]<q[0]:
        S.append(x)
        k+=1
        Q.insert((k,x[1]))
    else:
        Q.pop()
        S[q[1]].append(x)
        Q.insert((q[1],x[1]))

for i in range(len(S)):
    print(i,' ', S[i])


# Desc in nr min de subsiruri descresc
f=open("input.txt", "r")
L=f.readline().split()
S=[]
B=[]
S.append([L[0]])
B.append(L[0])
for x in L[1:]:
    if x>B[-1]:
        S.append([x])
        B.append(x)
    else:
        i = 0
        while B[i] < x:
            i += 1
        S[i].append(x)
        B[i]=x
print(S)
print(len(B))

f = open('input.txt')
l = [int(x) for x in f.readline().split()]
s = [[l[0]]]
b = [l[0]]
for x in l[1:]:
   if x > b[-1]:
       s.append([x])
       b.append(x)
   else:
       i = 0
       while b[i] < x:
           i += 1
       s[i].append(x)
       b[i] = x
print(s)
print(len(b))
"""
import collections
de=collections.deque([1,2,3])
de.popleft()
de.append(9)
de.appendleft(9)
print(de)
