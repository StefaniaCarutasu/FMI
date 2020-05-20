f=open("angajati.txt","r")
n=int(f.readline())
L=[]
l=[]
for i in range(n):
    aux=f.readline().split()
    aux2=""
    for j in range(len(aux)-2):
        aux2+=aux[j]+" "
    aux2=aux2.strip(" ")
    aux3=[aux2,int(aux[len(aux)-2]),int(aux[len(aux) - 1])]
    aux3=tuple(aux3)
    L.append(aux3)
f.close()
print(L)
nume=input()
smax=0
smediu=0
for i in L:
    if nume==i[0]:
        print("Angajatul ",nume, " ", "are varsta de ", i[1], "ani si salariul egal cu ", i[2])
    if i[2]>smax:
        smax=i[2]
    smediu+=i[2]
for i in L:
    if i[2]==smax:
        print(i[0])
smediu/=n
print("Salariul mediu din firma este ", smediu)
g=open("angajati_nume_txt","w")
L.sort(key=lambda x: x[0])
print(L)
for x in L:
    g.write(x[0])
g.close()
g=open("angajati_varsta_nume_txt","w")

L.sort(key=lambda x: x[0])
L.sort(key=lambda x: x[1], reverse=True)
print(L)
for x in L:
    g.write(x[0])

