import math
import matplotlib.pyplot as plt
import numpy as np

# 1
print("Exercitiul 1")
"""
    min = 40Hz
    max = 200Hz

    Daca luam B = 200 => f_c >= 2 * B = 2 * 200
"""
B = 200
f_c = 2 * B
print("Frecventa minima de esantionare este: ", f_c, '\n')

# 2
print("Exercitiul 2")
"""
    B = 10Hz
    f_c = 90Hz

    (2 * f_c - B) / m >= f_s >= (2 * f_c + B) / (m + 1)
"""


def ex2(B, f_c, m):
    left = (2 * f_c - B) / m
    right = (2 * f_c + B) / (m + 1)
    print("Pentru valoarea m = ", m, " avem: ")
    print(left, " >= f_s >= ", right, '\n')


B = 10
f_c = 90
# a: m = 1
ex2(B, f_c, 1)

# b: m = 2
ex2(B, f_c, 2)

# C: m = 4
ex2(B, f_c, 4)

# 3
"""
    f_c = 10
    f_s = 1000Hz
"""
f_c = 10
f_s = 1000
t = np.linspace(0, 1, num=f_s)
x = np.cos(2 * math.pi * f_c * t)

plt.plot(x)
plt.show()

X = np.fft.fft(x)
X = X[:500]

plt.plot(X)
plt.show()

