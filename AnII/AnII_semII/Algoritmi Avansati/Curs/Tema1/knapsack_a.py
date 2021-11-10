f = open("date_p2.in")
def citire():
    K = int(f.readline())
    S = []
    i = f.readline()
    while i:
        obiect = int(i)
        S.append(obiect)
        i = f.readline()
    return K, S, len(S)

K, S, n = citire()
matriceSol = [[0 for i in range(K + 1)] for j in range (n + 1)]

for i in range(1, n + 1):
    for j in range(1, K + 1):
        if j - S[i - 1] > 0:
            matriceSol[i][j] = max(matriceSol[i - 1][j], S[i - 1] + matriceSol[i - 1][j - S[i - 1]])
        else:
            matriceSol[i][j] = matriceSol[i - 1][j]

        print("Valoarea totala din rucsac este", matriceSol[n][K])

        #afisare obiecte
        while n > 0:
            if matriceSol[n - 1][K] == matriceSol[n][K]:
                n -= 1
            else:
                print(n, end=" ")
                K -= S[n - 1]
                n -= 1
        f.close()