import math
import numpy as np
import matplotlib.pyplot as plt

# 1
"""
    N = ?
    f_s = 44.1kHz
    distantarea binurilor DFT = 1Hz
"""


def ex1():
    print("Exercitiul 1")
    # f_s = 44.1 * 1000 #Hz
    # distantarea binurilor are ca formula f_s/N
    # f_s / N = 1 <=> 44100 / N = 1 => N = 44100 samples
    N = 44100 * 1
    print("Numar sample-uri necesare: ", N)


# 2
# a
"""
    A = 1
    fi = 0
    Nw = 200
"""


def sine(frequency, time, amplitude=1, phase=0):
    return amplitude * np.sin(2 * np.pi * frequency * time + phase)


def fereastraDreptunghiulara(n):
    fereastra = np.zeros(n)
    for i in range(n):
        fereastra[i] = 1.

    return fereastra


def fereastraHanning(n):
    fereastra = np.zeros(n)
    for i in range(n):
        fereastra[i] = 0.5 * (1 - math.cos(2 * math.pi * i / n))

    return fereastra


def fereastraHamming(n):
    fereastra = np.zeros(n)
    for i in range(n):
        fereastra[i] = 0.54 - 0.46 * math.cos(2 * math.pi * i / n)

    return fereastra


def fereastraBlackman(n):
    fereastra = np.zeros(n)
    for i in range(n):
        fereastra[i] = 0.42 - 0.5 * math.cos(2 * math.pi * i / n) + 0.08 * math.cos(6 * math.pi * i / n)

    return fereastra


def fereastraFlatTop(n):
    fereastra = np.zeros(n)
    for i in range(n):
        fereastra[i] = 0.22 - 0.42 * np.cos(2 * np.pi * i / n) + 0.28 * np.cos(6 * np.pi * i / n)
        + 0.007 * np.cos(8 * np.pi * i / n)

    return fereastra


def aplicaFereastra(x, fereastra):
    rezultat = np.zeros(x.shape)
    for i in range(len(rezultat)):
        if i < fereastra.shape[0]:
            rezultat[i] = x[i] * fereastra[i]
        else:
            rezultat[i] = 0.

    return rezultat


# b
"""
    f1 = 1000Hz
    f2 = 1100Hz
    f_s = 8000Hz
    N = 1000
"""

N = 1000
f1 = 1000
f2 = 1100
f_s = 8000

time_of_view = 0.25
n_samples = f_s * time_of_view + 1
time = np.linspace(0, time_of_view, int(n_samples))


def ex2_a():
    print("Exercitiul 2")
    fig, axs = plt.subplots(6, figsize=(6, 8))
    fig.tight_layout(pad=3.0)

    f_100 = 100
    n_samples_a = 200
    time_a = np.linspace(0, time_of_view, int(n_samples_a))

    sine100 = (sine(f_100, time_a))

    axs[0].set_title('Semnalul initial')
    axs[0].plot(time_a, sine100)

    # fereastra dreptunghiulara
    w1 = fereastraDreptunghiulara(200)
    filtrDreptunghiular = aplicaFereastra(sine100, w1)

    axs[1].set_title('Fereastra dreptunghiulara')
    axs[1].plot(time_a, filtrDreptunghiular)

    # fereastra Hanning
    w2 = fereastraHanning(200)
    filtrHanning = aplicaFereastra(sine100, w2)

    axs[2].set_title('Fereastra Hanning')
    axs[2].plot(time_a, filtrHanning)

    # fereastra Hamming
    w3 = fereastraHamming(200)
    filtrHamming = aplicaFereastra(sine100, w3)

    axs[3].set_title('Fereastra Hamming')
    axs[3].plot(time_a, filtrHamming)

    # fereastra Blackman
    w4 = fereastraBlackman(200)
    filtrBlackman = aplicaFereastra(sine100, w4)

    axs[4].set_title('Fereastra Blackman')
    axs[4].plot(time_a, filtrBlackman)

    # fereastra Flat Top
    w5 = fereastraFlatTop(200)
    filtrFlatTop = aplicaFereastra(sine100, w5)

    axs[5].set_title('Fereastra Flat Top')
    axs[5].plot(time_a, filtrFlatTop)

    plt.show()


def ex2_b():
    fig, axs = plt.subplots(3, figsize=(8, 6))
    fig.tight_layout(pad=3.0)

    time_of_view_b = 1
    fs = 8000
    n_samples_b = time_of_view_b * fs + 1
    time_b = np.linspace(0, time_of_view_b, int(n_samples_b))

    f1 = 1000
    f2 = 1100
    sine1 = sine(f1, time_b)
    sine2 = sine(f2, time_b)

    axs[0].set_title('Semnalele initiale')
    axs[0].plot(time_b, sine1)
    axs[0].plot(time_b, sine2)

    w = fereastraDreptunghiulara(1000)

    fft1 = np.abs(np.fft.fft(sine1, 8000))
    fft2 = np.abs(np.fft.fft(sine2, 8000))

    N_fft1 = len(fft1)
    N_fft2 = len(fft2)

    fft1_filtered = np.abs(np.fft.fft(aplicaFereastra(sine1, w)))
    fft2_filtered = np.abs(np.fft.fft(aplicaFereastra(sine2, w)))

    N_fft1_filtered = len(fft1_filtered)
    N_fft2_filtered = len(fft2_filtered)

    axs[1].set_title('FFT-ul semnalelor initiale')
    axs[1].plot(fft1[:N_fft1 // 2])
    axs[1].plot(fft2[:N_fft2 // 2])

    axs[2].set_title('FFT-ul ferestrelor')
    axs[2].plot(fft1_filtered[:N_fft1_filtered // 2])
    axs[2].plot(fft2_filtered[:N_fft2_filtered // 2])

    plt.show()


# 3
def ex3():
    print("Exercitiul 3")
    samples = 72  # sample-urile sunt la distanta de o ora si avem 72 de ore in 3 zile
    time_3 = np.linspace(0, 72, 72)
    f = open('trafic.csv')
    cars = []
    f.readline()
    for i in range(samples):
        x = int(f.readline().strip())
        cars.append(x)
    f.close()

    cars = np.array(cars)

    plt.figure()
    plt.grid(True)
    data_line, = plt.plot(time_3, cars, label='Data')

    lines_legend = [data_line]
    sizes = [5, 9, 13, 17]

    for size in sizes:
        cars_ext = np.pad(cars, (size - 1, 0), 'constant')
        medie_alunecatoare = np.convolve(cars_ext, np.ones(size) / size, 'valid')

        print("Media alunecatoare pentru w = " + str(size) + ":")
        print(medie_alunecatoare)

        line, = plt.plot(time_3[size:], medie_alunecatoare[size:], label='Window size = ' + str(size))
        lines_legend.append(line)

    plt.legend(handles=lines_legend)
    plt.show()


ex1()
ex2_a()
ex2_b()
ex3()
