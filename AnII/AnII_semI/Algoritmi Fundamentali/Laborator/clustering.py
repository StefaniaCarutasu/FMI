f = open("cuvinte.in")
def citireCuvinte():
    i = f.readline()
    cuvinte = i.split()
    return cuvinte

def distantaLevenshtein(cuv1, cuv2):
    n=len(cuv1)
    m=len(cuv2)
    M=[]
    for i in range(n+2):
        M.append([])
        for j in range(m+2):
                M[i].append(int('0'))
    for i in range(2,n+2):
        M[i][0]=cuv1[i-2]
    for i in range(2,m+2):
        M[0][i]=cuv2[i-2]
    for i in range(1,n+2):
        for j in range(1,m+2):
            if i == 1 and j == 1:
                if cuv1[0] == cuv2[0]:
                    M[1][1]=0
                else: M[1][1]=1
            elif j > 1 and i == 1:
                M[i][j] = M[i][j-1]+1
            elif i > 1 and j == 1:
                M[i][j] = M[i-1][j] + 1
            elif M[i][0] == M[0][j]:
                M[i][j] = M[i-1][j-1]
            else:
                M[i][j] = 1 + min(M[i-1][j-1], M[i][j-1], M[i-1][j])
    return M[n + 1][m + 1]

def clustering(cuvinte):
    #dictionarul practic contine nodurile si costurile muchiilor grafului complet
    d = {}
    for i in cuvinte:
        d[i] = []
        for j in cuvinte:
            d[i].append((j, distantaLevenshtein(i, j)))
    #facem vectorul de clase
    #fiecare cuvant e in propria lui clasa
    clasa = 0
    clase = []
    for i in d.keys():
        clase.append((i, clasa))
  



cuvinte = citireCuvinte()
clustering(cuvinte)