import numpy as np

f = open("date.in")
M = []
n = int(f.readline())   #citim numarul de puncte
i = 0
#citim punctele
while i < n:
    p = f.readline()
    M.append([float(p.split()[0]), float(p.split()[1])])
    i += 1

#citim punctul Q
Q = [float(x) for x in f.readline().split()]

semne = []
pozitie = "In interior"
#pentru fiecare latura a poligonului verific semnul determinantului si il adaug intr-un vector de semne
for j in range(len(M) - 1):
    p1, p2 = M[j], M[j + 1]
    array = np.array([[1, 1, 1], [p1[0], p2[0], Q[0]], [p1[1], p2[1], Q[1]]])
    det = np.linalg.det(array)
    semne.append(det)

array = np.array([[1, 1, 1], [M[len(M) - 1][0], M[0][0], Q[0]], [M[len(M) - 1][1], M[0][1], Q[1]]])
det = np.linalg.det(array)
semne.append(det)
#parcurg vectorul de semne si in functie de valoare afisez pozitia punctului Q
for i in semne:
    if i == 0:
        pozitie = "Pe laturi"
        break
    elif i < 0:
        pozitie = "In exterior"

print(pozitie)