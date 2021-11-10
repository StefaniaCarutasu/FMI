import numpy as np

f = open("date.in")

#citesc cele 3 puncte

P = [float(x) for x in f.readline().split()]
Q = [float(x) for x in f.readline().split()]
R = [float(x) for x in f.readline().split()]

print("P(", P[0], ",", P[1], ")", sep = "")
print("Q(", Q[0], ",", Q[1], ")", sep = "")
print("R(", R[0], ",", R[1], ")", sep = "")

#formez array-ul pentru a putea calcula determinantul
n_array = np.array([[1, 1, 1], [P[0], Q[0], R[0]], [P[1], Q[1], R[1]]])

det = np.linalg.det(n_array)

#in functie de valoarea determinantului afisez
if det == 0:
    print("Puncte coliniare")
elif det < 0:
    print("Viraj la dreapta")
else: print("Viraj la stanga")



