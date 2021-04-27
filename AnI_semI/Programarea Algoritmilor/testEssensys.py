f = open("date.in")
inf = float('inf')
import numpy

"""
#1
def citire():
    n1, n2 = f.readline().split()
    n1, n2 = int(n1), int(n2)
    m1 = []
    m2 = []
    for i in range(n2):
        l = f.readline().split()
        linie = [int(x) for x in l]
        m1.append(linie)
    for i in range(n1):
        l = f.readline().split()
        linie = [int(x) for x in l]
        m2.append(linie)
    return n1, m1, n2, m2

n1, m1, n2, m2 = citire()
ok = 0
for i in range(min(len(m1), len(m2))):
    for j in range(min(len(m1[i]), m2[i])):
        if m1[i][j] == m2[i][j]:
            print("Matricele au cel putin o valoare identica pe aceeasi pozitie")
            ok = 1
            break
if ok == 0:
    print("Matricele nu au nicio valoare identica pe aceeasi pozitie")


#2
print("Introduceti n: ")
n = int(input())
matrice = [[i for i in range(n)] for j in range(n)]
for i in matrice:
    print(*i)
print('\n')
for i in range(n):
    for j in range(n):
        if i < j:
            matrice[i][j], matrice[j][i] = matrice[j][i], matrice[i][j]
        else:
            pass

for i in matrice:
    print(*i)


#3
v = [0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0]

l = 0
lmax = 0

for i in range(len(v)):
    if i == 0:
        if v[i] == 1:
            l = 1
            lmax = 1
    elif v[i] == 1 and v[i - 1] == 1:
        l += 1
    elif v[i] == 1 and v[i - 1] == 0:
        l = 1
    elif v[i] == 0 and v[i - 1] == 1:
        if l > lmax:
            lmax = l

print("Lungimea maxima de cifre consecutive de 1 este:", lmax)


#5
n = int(input())
k = int(input())
max = k
for i in range(n):
    x = int(input())
    if max < x:
        max = x
sumGaussK = k(k + 1) / 2
sumGaussMax = max(max + 1) / 2
duplicat = sumGaussMax - sumGaussK
print(duplicat)
"""

#7
arr = [10, 4, 1, 6, 2]
p = numpy.prod(arr)
print(p)
a = []
for i in range(len(arr)):
    a.append(int(p / arr[i]))
print(a)