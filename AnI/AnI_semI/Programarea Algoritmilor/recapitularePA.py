"""
#merge sort
f = open("date.in")

def citire():
    v = f.readline().split()
    a = []
    for i in v:
        a.append(int(i))
    return a


def mergeSort(arr):
    if len(arr) > 1:

        # Finding the mid of the array
        mid = len(arr) // 2

        # Dividing the array elements
        L = arr[:mid]

        # into 2 halves
        R = arr[mid:]

        # Sorting the first half
        mergeSort(L)

        # Sorting the second half
        mergeSort(R)

        i = j = k = 0

        # Copy data to temp arrays L[] and R[]
        while i < len(L) and j < len(R):
            if L[i] < R[j]:
                arr[k] = L[i]
                i += 1
            else:
                arr[k] = R[j]
                j += 1
            k += 1

        # Checking if any element was left
        while i < len(L):
            arr[k] = L[i]
            i += 1
            k += 1

        while j < len(R):
            arr[k] = R[j]
            j += 1
            k += 1


# Code to print the list
def printList(arr):
    for i in range(len(arr)):
        print(arr[i], end=" ")
    print()


# Driver Code
if __name__ == '__main__':
    arr = citire()
    print("Given array is", end="\n")
    printList(arr)
    mergeSort(arr)
    print("Sorted array is: ", end="\n")
    printList(arr)

import copy
s = "www.mama.ro"
s = s.strip("w.")
print(s)
s = "Ana are {numar} mere {culoare}"
s = s.format(culoare = "rosii", numar = 7 )
print(s, '\n')

s = "amInTirile meLe"
t = s.upper()
print(t)
t = s.lower()
print(t)
t = s.swapcase()
print(t)
t = s.title()
print(t)
t = s.capitalize()
print(t, '\n')

s = "Ana are mere in camerele sale"
t = "mere"
x = s.count(t)
print(x)
x = s.count(t, 15)
print(x)
x = s.count(t, 15, 20)
print(x)
y = s.find(t)
print(y)

s = [1, 7, 2, 0, 6, 9]
s.sort()
t = s
t = "1 2 3 4 5"
t = t.split()
w = []
for i in t:
    w.append(int(i))
print(w)

x = ["Ana", "are", "mere", "multe"]
s = " ".join(x)
x = "Ana are mere multe!"
s = " ".join(x.split())
print(s)

l = [1, "ana", [1,2,2], (1,2)]
l = [x + 1 for x in range (10)]
l[1] = 11
l = [x**2 for x in range(10) if x % 2 == 0]
l = [int(x ** 2/ 2) if x % 2 == 0 else x ** 2 + 1 for x in range(10)]
L1 = [1, 3, 5, 6, 8, 3, 13, 21]
L2 = [18, 3, 7, 5, 16]
l = [x if x in L2 else 0 for x in L1]
print(l)
s = sum([int(c) if c % 2 == 0 else -c for c in range(20)])
print(s)
print(list("python"))
print(max(l))
l = [x % 4 for x in range(21)]
print(l)
n = l.count(2)
print(n)
l.append("casa")
l.insert(0, "casa")
print(l)

l = list("test")
l.extend("python")
l.reverse()
m = copy.deepcopy(l)
m.reverse()
print(l, m, sep='\n')

matrice = [[0 for i in range(10)] for j in range(10)]
k = 0
for i in range(len(matrice)):
    for j in range(len(matrice[i])):
        matrice[i][j] = k
        k += 1
for i in matrice:
    print(i)

t = 1, 2, 3
print(type(t))

t = (1,)
print(t, type(t), sep='\n')

t = (1, 2, 3, 5)
t = t[:3] + (4,) + t[3:]
print(t)
t = t[:3] + t[4:]
print(t)
t = (1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
t = t[:3] + (1, 2, 3) + t[7:]
print(t)
x = 11 in t
print(x)
t = (1,2,3)
y = t * 3
y = tuple("ana")

print(y, type(y),sep='\n')
print(min(y))
t = tuple(x % 2 for x in range(10) if x % 3 != 1)
print(t)
print(t.count(1))
x = 2
try:
    poz = t.index(x)
    print(x, "apare in t pe pozitia", poz)
except ValueError:
    print(x,"nu apare in t")
except:
    print("S-a produs o eroare")

#copierea unui tuplu
a = tuple([1, 2, 3, [4, 5, 6]])
print(a)
b = copy.deepcopy(a)
print(b)
a[3][1] = 10
print(a, b, sep = '\n')

t = 1, 2, 3
print(t, type(t))
x, y, z = t
print(x, type(x))
t = (243, "Carutasu", "Stefania", 10, 9.33)
grupa, *nume, medie = t
print(nume, type(nume))
matrice = ((1, 2, 3), (4, 5, 6), (7, 8, 9))
for linie in matrice:
    print(*linie)

s = "testare"
print(s, s.__hash__())

s = s[:len(s) - 1]
print(s, s.__hash__())

s = s + "e"
print(s, s.__hash__())

s = {-1, 4, 1, 2, 2, 2, 4, 5, -1, 8, -1}
print(s, type(s))
s = {x % 6 for x in range(25)}
t = tuple(x % 6 for x in range(25))
print(s, t, sep='\n')

x = {1, 2, 3}
y = {3, 2, 1}
print(x, y, x == y, x is y, sep='\n')
z = {4, 5, 6}
#| = reuniune, & = intersectie, - = diferenta, ^ = diferenta simetrica
print(z ^ y)
x = {1, 2, 3}
y = x | z
print(x <= y)
s = set("mort")
s.add('b')
s.discard('r')
s.update('c')
print(s)
print(x.union(y))
print("FROZENSET")
s = frozenset([1, 2, 3])
t = frozenset([4, 5, 6])
x = s.union(t)
print(*x)
print("DICTIONAR")
d = {"A": 1, 'B': 2, 6: 'X', (1,2,3): frozenset([1,2,3]) }
d['C'] = 16
print(d)
d['A'] = 12
print(d)
d = {chr(65 + x).lower(): x for x in range(5)}
print(d)
print(d.keys())
print(*d)
print(d.values())
print(d.items())

d = {chr(65 + x): x for x in range(10)}
t = {chr(65 + x): x * 100 for x in range(5, 8)}
print(d)
d.update(t)
print(d)
d.pop('E') #merge foarte bine
print(d)

s = "vreau si eu un job pls ms"
d = {c: s.count(c) for c in set(s)}
print(d)
"""
import copy

def suma(*args):
    s = 0
    for i in args:
        s += i
    return s
def sumaProd (x, y):
    return x + y, x * y
def schimbare(x):
    x = 100
def schimbare_lista(l):
    l.append(2)

#GENERATORI
def generator_numere_pare(n):
    x = 0
    while x <= n:
        yield x
        x += 2

s = suma()
print(s)
s = suma(7)
print(s)
s = suma(*(1,2,3))
print(s)
s = suma(*[1,2,3,4])
print(s)
x = 7
schimbare(x)
print(x)
l = [1,2,3]
print(l)
schimbare_lista(l)
print(l)

l = [2, 4, 1, 9, 5, 3]
l = sorted(l)
print(l)

n = 1234
suma = sum([int(c) for c in str(n)])
print(suma)

l = [123, 3, 21, 7, 91, 789, 9]
l.sort(key = lambda x: sum([int(c) for c in str(x)]))
print(l)

a = generator_numere_pare(20)
print(*a)

