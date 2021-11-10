# Carutasu Stefania 343

import numpy as np
import matplotlib.pyplot as plt

pi = np.pi

# 1
# a
"""
    fs = 2pi/T => nr de esantioane pe secunda (frecventa de esantionare)
"""
f_s = 2000
T = (2 * pi) / f_s
print("T = ", T)

# b
nr_esantioane = 3600 / T  # cate esantioane am intr-o ora
dimensiune_totala = nr_esantioane * 4 / 8  # dimensiunea in bytes
print("Dimensiunea necesara = ", dimensiune_totala)

# 2
"""
    x(t) = cos(200*pi*t)
    y(t) = cos(80*pi*t)
    z(t) = x(t) + y(t)
    
    Cosinusul este functie periodica de perioada 2pi
    => perioada lui x(t) = 2 * pi / 200 * pi = 1/100                                 
    => perioada lui y(t) = 2 * pi / 80 * pi = 1/40 
    => perioada lui z(t) = 1/20
"""

T_x = (2 * pi) / (200 * pi)
T_y = (2 * pi) / (80 * pi)
T_z = 1/np.gcd(int(1/T_x), int(1/T_y))

f_s = 2 * pi / T_z
f_N = 0.5 * f_s

print("fN = ", f_N)

# 3
"""
    x(t) = cos(520 * pi * t + pi/3)
    y(t) = cos(280 * pi * t - pi/3)
    z(t) = cos(120 * pi * t + pi/3)
"""

# a + b
no_samples = int(0.03 / 0.0005)
t = np.linspace(0, 0.03, no_samples)

x = np.cos(520 * pi * t + pi / 3)
y = np.cos(280 * pi * t - pi / 3)
z = np.cos(120 * pi * t + pi / 3)

fig, axs = plt.subplots(3)
fig.suptitle("Plots subpuncte a + b")
axs[0].plot(t, x, 'b')
axs[1].plot(t, y, 'r')
axs[2].plot(t, z, 'g')

# show the plot
plt.show()

# c + d
"""
    x[n] = x(nT)
    f_s = 2*pi/T
"""
f_s = 200
T = 2 * pi / f_s

no_samples = round(0.03 * 200) + 1
at = np.linspace(0, 0.03, no_samples)
x_n = np.cos(520 * pi * at + pi / 3)
y_n = np.cos(280 * pi * at - pi / 3)
z_n = np.cos(120 * pi * at + pi / 3)

fig2, axs2 = plt.subplots(3)
fig2.suptitle("Plots subpuncte c + d")
axs2[0].plot(t, x, 'b')
axs2[0].plot(at, x_n, 'o', color='yellow')
axs2[1].plot(t, y, 'r')
axs2[1].plot(at, y_n, 'o', color='yellow')
axs2[2].plot(t, z, 'g')
axs2[2].plot(at, z_n, 'o', color='yellow')
plt.show()
# 4
"""
    SNR_dB = 10lg(P_semnal/P_zgomot)
    => SNR_dB = 10lg(P_semnal) - 10lg(P_zgomot)
    => SNR_dB = P_semnal_dB - P_zgomot_dB
"""
P_semnal_dB = 80  # dB
SNR_dB = 90  # dB
P_zgomot_dB = SNR_dB - P_semnal_dB
print("P_zgomot = ", P_zgomot_dB)
