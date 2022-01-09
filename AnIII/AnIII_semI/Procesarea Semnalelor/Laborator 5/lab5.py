import numpy as np
import scipy.signal
import matplotlib.pyplot as plt


def fereastraDreptunghiulara(n):
    fereastra = np.zeros(n)
    for i in range(n):
        fereastra[i] = 1.

    return fereastra


def fereastraHanning(n):
    fereastra = np.zeros(n)
    for i in range(n):
        fereastra[i] = 0.5 * (1 - np.cos(2 * np.pi * i / n))

    return fereastra


def fereastraHamming(n):
    fereastra = np.zeros(n)
    for i in range(n):
        fereastra[i] = 0.54 - 0.46 * np.cos(2 * np.pi * i / n)

    return fereastra


def fereastraBlackman(n):
    fereastra = np.zeros(n)
    for i in range(n):
        fereastra[i] = 0.42 - 0.5 * np.cos(2 * np.pi * i / n) + 0.08 * np.cos(6 * np.pi * i / n)

    return fereastra


def fereastraFlatTop(n):
    fereastra = np.zeros(n)
    for i in range(n):
        fereastra[i] = 0.22 - 0.42 * np.cos(2 * np.pi * i / n) + 0.28 * np.cos(6 * np.pi * i / n)
        + 0.007 * np.cos(8 * np.pi * i / n)

    return fereastra


def aplicaFereastra(numeFereastra, fereastra):
    w, h = scipy.signal.freqz(fereastra)

    plt.suptitle(numeFereastra)
    plt.xlabel("Frecventa")
    plt.ylabel("Putere")

    plt.plot(w, 20 * np.log10(np.abs(h) + 1))
    plt.show()


def ex1():
    dimensiuneFereastra = 32

    aplicaFereastra("Fereastra dreptunghiulara", fereastraDreptunghiulara(dimensiuneFereastra))
    aplicaFereastra("Fereastra Hanning", fereastraHanning(dimensiuneFereastra))
    aplicaFereastra("Fereastra Hamming", fereastraHamming(dimensiuneFereastra))
    aplicaFereastra("Fereastra Blackman", fereastraBlackman(dimensiuneFereastra))
    aplicaFereastra("Fereastra Flat Top", fereastraFlatTop(dimensiuneFereastra))


def ex2():
    traffic_data = np.genfromtxt('trafic.csv')

    # 2b
    samplingPeriod = 3600
    samplingRate = 1 / samplingPeriod
    limitaNyquist = samplingRate / 2

    frecventaLowPass = samplingRate / 4

    print(f'Frecvența de tăiere: {frecventaLowPass:.8f} Hz')

    frecventaLowPass = frecventaLowPass / limitaNyquist

    print("Frecventa de taiere ", frecventaLowPass, " * frecventa Nyquist")

    # 2a
    X = np.fft.fft(traffic_data)
    X_mag = np.abs(X)

    frecv_normalizate = np.linspace(0, 1, len(X))

    plt.plot(frecv_normalizate, X_mag)
    plt.xlabel("Frecventa")
    plt.ylabel("Amplitudinea")

    plt.show()

    # 2c
    ordine = 5
    atenuare = 5

    butter_b, butter_a = scipy.signal.butter(ordine, frecventaLowPass)
    cheby_b, cheby_a = scipy.signal.cheby1(ordine, atenuare, frecventaLowPass)

    # 2d
    _, axs = plt.subplots(1, 2, figsize=(11, 3))

    w, h = scipy.signal.freqz((butter_b, butter_a))
    axs[0].plot(w, 20 * np.log10(np.abs(h) + 1))
    axs[0].set_title("Raspuns filtru Butterworth")

    w, h = scipy.signal.freqz(cheby_b, cheby_a)
    axs[1].plot(w, 20 * np.log10(np.abs(h) + 1))
    axs[1].set_title("Raspuns filtru Chebyshev")

    plt.show()

    # 2e
    butter_y = scipy.signal.filtfilt(butter_b, butter_a, traffic_data)
    cheby_y = scipy.signal.filtfilt(cheby_b, cheby_a, traffic_data)

    nrZile = 3
    limita = nrZile * 24

    plt.figure(figsize=(11, 5))

    plt.suptitle(f"Datele pe {nrZile} zile")

    plt.plot(traffic_data[:limita], label="Semnal original")
    plt.plot(butter_y[:limita], label="Filtru Butterworth")
    plt.plot(cheby_y[:limita], label="Filtru Chebyshev")

    plt.legend()
    plt.show()

    # 2f
    ordine = 5
    atenuare = 10
    b, a = scipy.signal.cheby1(ordine, atenuare, frecventaLowPass)

    nrZile = 5
    limita = nrZile * 24
    x = traffic_data[:limita]
    y = scipy.signal.filtfilt(b, a, x)

    plt.figure(figsize=(11, 5))
    plt.suptitle(f"Datele pe {nrZile} zile")
    plt.plot(x, color='blue', label='Original')
    plt.plot(y, color='orange', label='Filtrat')

    plt.legend()
    plt.show()


#ex1()
ex2()
